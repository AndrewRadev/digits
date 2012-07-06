#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "image.h"
#include "matrix.h"

Image* image_convolution(Image* image, Matrix* matrix);
int pixel_convolution(Image* image, Matrix* matrix, int top, int left);

#endif
