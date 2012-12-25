#ifndef BLUR_H
#define BLUR_H
#include "image.h"


void gaussian_blur(png_image *img, int blur_sz, double sigma);
#endif
