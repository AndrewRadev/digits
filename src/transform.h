#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "image.h"

Image* image_scale(Image* image, int new_width, int new_height, int padding);
int bilinear_intensity(Image* image, float x, float y, int padding);

#endif
