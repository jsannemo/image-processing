#include "image.h"

png_image base;

void set_channel(char *dest, char* source, png_image* img);

int main(int argc, char **argv){
	if(argc < 5) {
		printf("Usage: input output source target\n");
		return 1;	
	}
	char *filename = argv[1];
	int ok = read_png_image(filename, &base);
	if(!ok){
		printf("Could not read .png (missing? broken? not RGBA?)\n");
		return 1;	
	}
	set_channel(argv[3], argv[4], &base);	

	if(!write_png_image(argv[2], &base)){
		printf("Could not write .png\n");
		return 1;
	}
	return 0;
}

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

