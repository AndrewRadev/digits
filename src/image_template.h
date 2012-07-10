#ifndef IMAGE_TEMPLATE_H
#define IMAGE_TEMPLATE_H

#include "image.h"
#include "matrix.h"

typedef struct ImageTemplate {
	int digit;
	Image* image;
	Matrix* matrix;
	int threshold;
	float rotation;
} ImageTemplate;

ImageTemplate* new_image_template(int digit, const char* filename, int threshold);
void print_image_match(ImageTemplate* image_template, int certainty);
void free_image_template(ImageTemplate* image_template);

#endif
