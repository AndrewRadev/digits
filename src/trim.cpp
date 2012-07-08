#include "dbg.h"
#include "image.h"
#include "trim.h"

Image* image_trim(Image* image, int blank_value) {
	int width  = image_width(image);
	int height = image_height(image);

	int top    = 0;
	int bottom = height - 1;
	int left   = 0;
	int right  = width - 1;

left_to_right:
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (image_get_pixel_intensity(image, x, y) != blank_value) {
				left = x;
				goto right_to_left;
			}
		}
	}

right_to_left:
	for (int x = width - 1; x >= 0; x--) {
		for (int y = 0; y < height; y++) {
			if (image_get_pixel_intensity(image, x, y) != blank_value) {
				right = x;
				goto top_to_bottom;
			}
		}
	}

top_to_bottom:
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (image_get_pixel_intensity(image, x, y) != blank_value) {
				top = y;
				goto bottom_to_top;
			}
		}
	}

bottom_to_top:
	for (int y = height - 1; y >= 0; y--) {
		for (int x = 0; x < width; x++) {
			if (image_get_pixel_intensity(image, x, y) != blank_value) {
				bottom = y;
				goto finish;
			}
		}
	}

finish:
	Image* trimmed_image = image_blank_copy(image, right - left + 1, bottom - top + 1);

	for (int x = 0; x < image_width(trimmed_image); x++) {
		for (int y = 0; y < image_height(trimmed_image); y++) {
			int intensity = image_get_pixel_intensity(image, left + x, top + y);
			image_set_pixel_intensity(trimmed_image, x, y, intensity);
		}
	}

	return trimmed_image;
}
