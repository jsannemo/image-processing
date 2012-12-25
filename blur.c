#include "blur.h"
#include "image.h"
#include "math.h"

void gaussian_blur(png_image *img, int blur_sz, double sigma){
	int height = img->height;
	int width = img->width;
	printf("sigma is %lf\n", sigma); 
	double matrix[blur_sz][blur_sz];
	double sum = 0;
	for(int i = 0; i<blur_sz; i++)
		for(int j = 0; j<blur_sz; j++){
			int dx = (blur_sz/2)-i;
			int dy = (blur_sz/2)-j;
			matrix[i][j] = exp(-(dx*dx + dy*dy)/(2*sigma*sigma))/(2*M_PI*sigma*sigma);
			sum += matrix[i][j];
		}

	double fct = 1.0/sum;
	for(int i = 0; i<blur_sz; i++)
		for(int j = 0; j<blur_sz; j++)
			matrix[i][j] *= fct;

	for(int i = 0; i<height; i++)
		for(int j = 0; j<width; j++){
			double n[4];
			memset(n, 0, sizeof(n));
			int count = 0;
			for(int r = 0; r<blur_sz; r++)
				for(int c = 0; c<blur_sz; c++){
					int nr = i + r - (blur_sz/2);
 					int nc = j + c - (blur_sz/2);
					if(nr < 0 || nc < 0 || nr >= height || nc >= width) continue;
					count++; 
					png_byte* row = img->row_pointers[nr];
					png_byte* ptr = &(row[nc*4]);
					for(int k = 0; k<4; k++) n[k] += ptr[k]*matrix[r][c];
				}
			
			png_byte* row = img->row_pointers[i];
			png_byte* ptr = &(row[j*4]);
			for(int k = 0; k<4; k++){
				ptr[k] = (int) (n[k]);	
			}

		}	
};
