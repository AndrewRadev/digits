#include "image_template.h"

ImageTemplate* new_image_template(int digit, const char* filename, int threshold) {
	ImageTemplate* image_template = (ImageTemplate*)malloc(sizeof(ImageTemplate));

	image_template->digit     = digit;
	image_template->image     = image_invert(image_from_file(filename));
	image_template->matrix    = image_to_intensity_matrix(image_template->image);
	image_template->threshold = threshold;
	image_template->rotation  = 0;

	return image_template;
}

void print_image_match(ImageTemplate* image_template, int certainty) {
	printf("Matched digit: %d\n", image_template->digit);
	printf("Rotation: %d\n", (int)image_template->rotation);
	printf("Certainty: %d%% (minimum for a sure match is %d%%)\n", certainty, image_template->threshold);
}

void free_image_template(ImageTemplate* image_template) {
	free_matrix(image_template->matrix);
	free_image(image_template->image);
	free(image_template);
}
