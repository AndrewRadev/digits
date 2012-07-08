#include "dbg.h"
#include "transform.h"
#include "image.h"
#include <cassert>

Image* image_scale(Image* image, int new_width, int new_height, int padding) {
	int width     = image_width(image);
	int height    = image_height(image);
	float x_ratio = (float)width / (float)new_width;
	float y_ratio = (float)height / (float)new_height;
	Image* output = image_blank_copy(image, new_width, new_height);

	for (int y = 0; y < new_height; y++) {
		for (int x = 0; x < new_width; x++) {
			float original_y = (int)y * y_ratio;
			float original_x = (int)x * x_ratio;
			int intensity    = image_get_pixel_intensity(image, original_x, original_y);

			// int intensity = bilinear_intensity(image, original_x, original_y, padding);

			image_set_pixel_intensity(output, x, y, intensity);
		}
	}

	return output;
}

int bilinear_intensity(Image* image, float x, float y, int padding) {
	int left_x   = (int)x;
	int top_y    = (int)y;
	int right_x  = left_x + 1;
	int bottom_y = top_y + 1;

	float delta_y = y - top_y;
	float delta_x = x - left_x;

	if (right_x < image_width(image) && bottom_y < image_height(image)) {
		int top    = (1 - delta_x)*image_get_pixel_intensity(image, left_x, top_y) + delta_x*image_get_pixel_intensity(image, right_x, top_y);
		int bottom = (1 - delta_x)*image_get_pixel_intensity(image, left_x, bottom_y) + delta_x*image_get_pixel_intensity(image, right_x, bottom_y);

		return (1 - delta_y)*top + delta_y*bottom;
	} else if (right_x < image_width(image)) {
		int top    = (1 - delta_x)*image_get_pixel_intensity(image, left_x, top_y) + delta_x*image_get_pixel_intensity(image, right_x, top_y);
		int bottom = padding;

		return (1 - delta_y)*top + delta_y*bottom;
	} else if (bottom_y < image_height(image)) {
		int top    = (1 - delta_x)*image_get_pixel_intensity(image, left_x, top_y) + delta_x*padding;
		int bottom = (1 - delta_x)*image_get_pixel_intensity(image, left_x, bottom_y) + delta_x*padding;

		return (1 - delta_y)*top + delta_y*bottom;
	} else {
		int top    = (1 - delta_x)*image_get_pixel_intensity(image, left_x, top_y) + delta_x*padding;
		int bottom = padding;

		return (1 - delta_y)*top + delta_y*bottom;
	}
}
