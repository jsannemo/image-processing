#include "image.h"
#include "blur.h"
#include "stdio.h"
#include "channel.h"

png_image base;

int main(int argc, char **argv){
	if(argc < 4) {
		printf("Usage: jsgfx input output transform [arguments]\n");
		return 1;	
	}
	char *filename = argv[1];
	int ok = read_png_image(filename, &base);
	if(!ok){
		printf("Could not read .png (missing? broken? not RGBA?)\n");
		return 1;	
	}

	char *transform = argv[3];
	if(!strcmp(transform, "blur")){
		if(argc < 6){
			printf("Blur takes arguments <blur_radius> <sigma>\n");		
			return 1;		
		}
		int rad = atoi(argv[4]);
		double sigma = atof(argv[5]);
		gaussian_blur(&base, rad, sigma);	
	}
	if(!strcmp(transform, "channel")){
		if(argc < 6){
			printf("Channel takes argument <dest = r,g,b> <source = r,g,b,int>\n");
			return 1;
		}	
		set_channel(argv[4], argv[5], &base);		
	}

	if(!write_png_image(argv[2], &base)){
		printf("Could not write .png\n");
		return 1;
	}
	return 0;
}
