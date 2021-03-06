#include "dbg.h"
#include "transform.h"
#include "image.h"
#include <cassert>

float degrees_to_radians(float angle) {
	return (angle * 3.14159265) / 180.0;
}

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

Image* image_rotate(Image* image, float angle, int padding) {
	int width     = image_width(image);
	int height    = image_height(image);
	Image* output = image_blank_copy(image, width, height);

	float radians = degrees_to_radians(angle);
	int mid_x     = width / 2;
	int mid_y     = height / 2;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float original_x = cos(radians)*(x - mid_x) + sin(radians)*(y - mid_y) + mid_x;
			float original_y = -sin(radians)*(x - mid_x) + cos(radians)*(y - mid_y) + mid_y;

			if (original_x >= width || original_y >= height || original_x < 0 || original_y < 0) {
				image_set_pixel_intensity(output, x, y, padding);
			} else {
				// int intensity = image_get_pixel_intensity(image, original_x, original_y);
				int intensity = bilinear_intensity(image, original_x, original_y, padding);

				image_set_pixel_intensity(output, x, y, intensity);
			}
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

float min_rotation_step(Image* image) {
	int width  = image_width(image);
	int height = image_height(image);
	int mid_x  = width / 2;
	int mid_y  = height / 2;

	float degrees   = 45;
	float radians   = degrees_to_radians(45);
	float x         = 0;
	float y         = 0;
	float current_x = 0;
	float current_y = 0;
	float next_x    = cos(radians)*(x - mid_x) + sin(radians)*(y - mid_y) + mid_x;
	float next_y    = -sin(radians)*(x - mid_x) + cos(radians)*(y - mid_y) + mid_y;

	do {
		current_x = next_x;
		current_y = next_y;

		degrees /= 2.0;
		radians = degrees_to_radians(degrees);

		next_x = cos(radians)*(x - mid_x) + sin(radians)*(y - mid_y) + mid_x;
		next_y = -sin(radians)*(x - mid_x) + cos(radians)*(y - mid_y) + mid_y;
	} while (abs(next_x - current_x) > 1 || abs(next_y - current_y) > 1);

	return degrees;
}
