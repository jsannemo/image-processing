#include <png.h>
#include "image.h"

int read_png_image(char *file_name, png_image *img) {
	/* read png header and compare to sig */
	unsigned char header[8];

    FILE *fp = fopen(file_name, "rb");
    if (!fp){
		printf("Could not open file for reading\n");
		return 0;
	}
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)){
		printf("Not a PNG file\n");
		return 0;
	}

	/* initilize structures */
    img->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!img->png_ptr){
		printf("Could not initialize read struct\n");
		return 0;
	}

    img->info_ptr = png_create_info_struct(img->png_ptr);
    if (!img->info_ptr){
		printf("Could not initialize info struct\n");
		return 0;
	}

    if (setjmp(png_jmpbuf(img->png_ptr))){
		printf("Read error (metadata)\n");
        return 0;
	}

	/* read metadata */
    png_init_io(img->png_ptr, fp);
    png_set_sig_bytes(img->png_ptr, 8);

    png_read_info(img->png_ptr, img->info_ptr);

    img->width = png_get_image_width(img->png_ptr, img->info_ptr);
    img->height = png_get_image_height(img->png_ptr, img->info_ptr);
    img->color_type = png_get_color_type(img->png_ptr, img->info_ptr);
    img->bit_depth = png_get_bit_depth(img->png_ptr, img->info_ptr);

    img->number_of_passes = png_set_interlace_handling(img->png_ptr);
    png_read_update_info(img->png_ptr, img->info_ptr);


    /* read image data */
    if (setjmp(png_jmpbuf(img->png_ptr))){
		printf("Read error (image data)\n");
        return 0;
	}

    img->row_pointers = png_malloc(img->png_ptr, sizeof(png_bytep) * img->height);

    for (int y=0; y<img->height; y++)
            img->row_pointers[y] = png_malloc(img->png_ptr, png_get_rowbytes(img->png_ptr, img->info_ptr));

    png_read_image(img->png_ptr, img->row_pointers);

    fclose(fp);

	/* ensure correct color type (only supports rgba) */
    if (png_get_color_type(img->png_ptr, img->info_ptr) == PNG_COLOR_TYPE_RGB){
		printf("Wrong image type (missing alpha)\n");
		return 0;
	}

    if (png_get_color_type(img->png_ptr, img->info_ptr) != PNG_COLOR_TYPE_RGBA){
		printf("Wrong image type (not RGBA)\n");
       return 0;
	}
	return 1;
}

int write_png_image(char *file_name, png_image *img){
    /* create file */
    FILE *fp = fopen(file_name, "wb");
    if (!fp){
		printf("Could not open file for writing\n");
		return 0;
	}

    /* initialize structs */
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr) {
		printf("Could not create write struct\n");
		return 0;
	}

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr){
		printf("Could not create info struct\n");
		return 0;
	}

    if (setjmp(png_jmpbuf(png_ptr))){
		printf("Could not open IO\n");
		return 0;
	}

    png_init_io(png_ptr, fp);


    /* write header */
    if (setjmp(png_jmpbuf(png_ptr))){
		printf("Could not write header\n");
		return 0;
	}

    png_set_IHDR(png_ptr, info_ptr, img->width, img->height,
                 img->bit_depth, img->color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);


    /* write image data */
    if (setjmp(png_jmpbuf(png_ptr))){
		printf("Could not write image data\n");
		return 0;
	}

    png_write_image(png_ptr, img->row_pointers);


    /* end write */
    if (setjmp(png_jmpbuf(png_ptr))){
		printf("Could not write end\n");
		return 0;
	}

    png_write_end(png_ptr, NULL);
    fclose(fp);
	return 1;
}

void clear_png_image(png_image *img){
    for (int y=0; y<img->height; y++)
            free(img->row_pointers[y]);
    free(img->row_pointers);
}
