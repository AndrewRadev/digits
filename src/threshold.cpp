#include <cassert>
#include "image.h"
#include "threshold.h"

Image* image_threshold(Image* image, int value) {
	Image* output = image_blank_copy(image);
	int height    = image_height(image);
	int width     = image_width(image);

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			int intensity = image_get_pixel_intensity(image, x, y);

			if (intensity > value) {
				image_set_pixel_intensity(output, x, y, 255);
			} else {
				image_set_pixel_intensity(output, x, y, 0);
			}
		}
	}

	return output;
}

Image* image_iterative_threshold(Image* image) {
	int height         = image_height(image);
	int width          = image_width(image);
	int previous_value = -1;
	int current_value  = 128;

	while (current_value != previous_value) {
		int background_values = 0;
		int background_count  = 0;
		int foreground_values = 0;
		int foreground_count  = 0;

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				int intensity = image_get_pixel_intensity(image, x, y);

				if (intensity > current_value) {
					foreground_values += intensity;
					foreground_count += 1;
				} else {
					background_values += intensity;
					background_count += 1;
				}
			}
		}

		previous_value = current_value;
		int background_average = background_values / (float)background_count;
		int foreground_average = foreground_values / (float)foreground_count;
		current_value = (int)((background_average + foreground_average) / 2.0);
	}

	return image_threshold(image, current_value);
}
