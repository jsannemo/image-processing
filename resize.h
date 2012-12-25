#ifndef RESIZE_H
#define RESIZE_H

#include "image.h"

void change_size(png_image *img, int nheight, int nwidth);
int clip(png_image *img, int nheight, int nwidth, int y, int x);


#endif
