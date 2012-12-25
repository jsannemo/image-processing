#include "image.h"
#include "blur.h"
#include "stdio.h"
#include "resize.h"

png_image base;

int main(int argc, char **argv){
	if(argc < 4) {
		printf("Usage: input output command [arguments]\n");
		return 1;	
	}
	char *filename = argv[1];
	int ok = read_png_image(filename, &base);
	if(!ok){
		printf("Could not read .png (missing? broken? not RGBA?)\n");
		return 1;	
	}
	char* command = argv[3];
	if(!strcmp(command, "size")){
		if(argc == 6){
			int width = atoi(argv[4]);
			int height = atoi(argv[5]);
			change_size(&base, height, width);
		} else {
			printf("Usage: size width height\n");	
			return 1;	
		}
	} else if(!strcmp(command, "clip")){
		if(argc == 8){
			int x = atoi(argv[4]);
			int y = atoi(argv[5]);
			int width = atoi(argv[6]);
			int height = atoi(argv[7]);
			clip(&base, height, width, y, x);
		} else {
			printf("Usage: clip x y width height\n");
		}
	} else {
		printf("Commands supported: size\n");
		return 1;
	}
	if(!write_png_image(argv[2], &base)){
		printf("Could not write .png\n");
		return 1;
	}
	return 0;
}
