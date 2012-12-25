#include "image.h"
#include "blur.h"
#include "stdio.h"

png_image base;

int main(int argc, char **argv){
	if(argc < 5) {
		printf("Usage: input output blur_radius sigma\n");
		return 1;	
	}
	char *filename = argv[1];
	int ok = read_png_image(filename, &base);
	if(!ok){
		printf("Could not read .png (missing? broken? not RGBA?)\n");
		return 1;	
	}
	int rad = atoi(argv[3]);
	double sigma = atof(argv[4]);
	gaussian_blur(&base, rad, sigma);	

	if(!write_png_image(argv[2], &base)){
		printf("Could not write .png\n");
		return 1;
	}
	return 0;
}
