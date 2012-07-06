#include <cassert>
#include "image.h"
#include "threshold.h"

Image* image_threshold(Image* image, int value) {
	Image* output = image_blank_copy(image);
	int height    = image_height(image);
	int width     = image_width(image);

	for (int j = 0; j < width; j++) {
		for (int i = 0; i < height; i++) {
			int intensity = image_get_pixel_intensity(image, i, j);

			if (intensity > value) {
				image_set_pixel_intensity(output, i, j, 255);
			} else {
				image_set_pixel_intensity(output, i, j, 0);
			}
		}
	}

	return output;
}

// TODO: consider using Otsu
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

		for (int j = 0; j < width; j++) {
			for (int i = 0; i < height; i++) {
				int intensity = image_get_pixel_intensity(image, i, j);

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
