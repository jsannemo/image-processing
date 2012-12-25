#include "channel.h"
#include "image.h"

void set_channel(char *dest, char* source, png_image* img){

	int destw = dest[0] == 'r' ? 0 : dest[0] == 'g' ? 1 : dest[0] == 'b' ? 2 : dest[0] == 'a' ? 3 : -1;
	if(destw < 0) return;	
	int sourcew = source[0] == 'r' ? -1 : source[0] == 'g' ? -2 : source[0] == 'b' ? -3 : source[0] == 'a' ? -4 : 0;
	if(!sourcew) sourcew = atoi(source);
	int height = img->height;
	int width = img->width;
	for(int i = 0; i<height; i++)
		for(int j = 0; j<width; j++){
			png_byte* row = img->row_pointers[i];
			png_byte* ptr = &(row[j*4]);	
			ptr[destw] = sourcew >= 0 ? sourcew : ptr[-sourcew-1];	
		}
}

