#ifndef IMAGE_H
#define IMAGE_H
#include <png.h>
#include <stdlib.h>

#define png_sig_sz 8

/* PNG rgba image */
typedef struct {
	int width, height;
	png_byte color_type;
	png_byte bit_depth;

	png_structp png_ptr;
	png_infop info_ptr;
	int number_of_passes;
	png_bytep * row_pointers;

} png_image;


int read_png_image(char *file_name, png_image *img);
int write_png_image(char *file_name, png_image *img);
void clear_png_image(png_image *img);

#endif
