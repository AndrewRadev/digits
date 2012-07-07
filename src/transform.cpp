#include "dbg.h"
#include "transform.h"
#include "image.h"

Image* image_scale(Image* image, int new_width, int new_height) {
	int width     = image_width(image);
	int height    = image_height(image);
	float x_ratio = (float)width / (float)new_width;
	float y_ratio = (float)height / (float)new_height;
	Image* output = image_blank_copy(image, new_width, new_height);

	for (int y = 0; y < new_height; y++) {
		for (int x = 0; x < new_width; x++) {
			int original_y = (int)y * y_ratio;
			int original_x = (int)x * x_ratio;
			int intensity  = image_get_pixel_intensity(image, original_x, original_y);
			image_set_pixel_intensity(output, x, y, intensity);
		}
	}

	return output;
}
