#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>
#include <easybmp/EasyBMP.h>
#include "matrix.h"

typedef BMP Image;
typedef RGBApixel Pixel;
typedef ebmpBYTE Byte;

Image *image_from_file(const char *filename);
Image *image_blank_copy(Image* image, int width, int height);
Image *image_blank_copy(Image* image);
void free_image(Image* image);

int image_height(Image* image);
int image_width(Image* image);
Pixel &image_get_pixel(Image* image, int i, int j);
int image_get_pixel_intensity(Image* image, int i, int j);
void image_set_pixel_intensity(Image* image, int i, int j, int intensity);
int image_invert(Image* image);

Matrix* image_to_intensity_matrix(Image* image);
void image_to_file(Image* image, const char* filename);

#endif
