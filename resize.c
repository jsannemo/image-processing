#include "resize.h"
#include "image.h"
#include "png.h"
#include "stdlib.h"
#include "assert.h"

void change_size(png_image *img, int nheight, int nwidth){
	assert(nheight >= 0 && nwidth >= 0);
	png_bytep *nrow_pointers = png_malloc(img->png_ptr, sizeof(png_bytep) * nheight);
	int oheight = img->height;
	int owidth = img->width;
	img->info_ptr->height = nheight;
	img->info_ptr->width = nwidth;
	img->height = nheight;
	img->width = nwidth;
	for(int y = 0; y<nheight; y++){
		nrow_pointers[y] = png_malloc(img->png_ptr, png_get_rowbytes(img->png_ptr, img->info_ptr));	
	}
	for(int y = 0; y<nheight; y++)
		for(int x = 0; x<nwidth; x++){
			png_byte* row = nrow_pointers[y];
			png_byte* ptr = &(row[x*4]);
			png_byte* orow = img->row_pointers[y];
			png_byte* optr = &(row[x*4]);
			if(y < oheight && x < owidth){
				for(int k = 0; k<4; k++) ptr[k] = optr[k];  				
			} else {
				memset(ptr, 0, 4*sizeof(png_byte));
			}
		}	
}

int clip(png_image *img, int nheight, int nwidth, int y, int x){
	assert(nheight >= 0 && nwidth >= 0 && y >= 0 && x >= 0);
	for(int yy = 0; yy<nheight; yy++)
		for(int xx = 0; xx<nwidth; xx++){
			png_byte* col = &(img->row_pointers[yy][4*xx]);
			if(yy+y < (img->height) && xx+x < (img->width)){
				png_byte* ocol = &(img->row_pointers[yy+y][4*(xx+x)]);
				for(int k = 0; k<4; k++) col[k] = ocol[k];
			} else {
				for(int k = 0; k<4; k++) memset(col, 0, 4*sizeof(png_byte));
			}
		}
	change_size(img, nheight, nwidth);
}

