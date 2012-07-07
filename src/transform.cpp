#include "dbg.h"
#include "transform.h"
#include "image.h"
#include <cassert>

Image* image_scale(Image* image, int new_width, int new_height) {
	int width     = image_width(image);
	int height    = image_height(image);
	float x_ratio = (float)width / (float)new_width;
	float y_ratio = (float)height / (float)new_height;
	Image* output = image_blank_copy(image, new_width, new_height);

	for (int y = 0; y < new_height; y++) {
		for (int x = 0; x < new_width; x++) {
			float original_y = (int)y * y_ratio;
			float original_x = (int)x * x_ratio;
			int intensity    = bilinear_intensity(image, original_x, original_y);

			image_set_pixel_intensity(output, x, y, intensity);
		}
	}

	return output;
}

int bilinear_intensity(Image* image, float x, float y) {
	int left_x   = (int)x;
	int top_y    = (int)y;
	int right_x  = left_x + 1;
	int bottom_y = top_y + 1;

	float delta = -1.0;

	if (right_x < image_width(image) && bottom_y < image_height(image)) {
		delta  = x - left_x;
		int top    = (1 - delta)*image_get_pixel_intensity(image, left_x, top_y) + delta*image_get_pixel_intensity(image, right_x, top_y);
		int bottom = (1 - delta)*image_get_pixel_intensity(image, left_x, bottom_y) + delta*image_get_pixel_intensity(image, right_x, bottom_y);

		delta = y - top_y;

		return (1 - delta)*top + delta*bottom;
	} else if (right_x < image_width(image)) {
		delta  = x - left_x;
		return image_get_pixel_intensity(image, (1 - delta)*left_x + delta*right_x, top_y);
	} else if (bottom_y < image_height(image)) {
		delta  = y - top_y;
		return image_get_pixel_intensity(image, x, (1 - delta)*top_y + delta*bottom_y);
	} else {
		return image_get_pixel_intensity(image, left_x, top_y);
	}
}
