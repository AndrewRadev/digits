#include "image.h"
#include "util.h"

// Note: Assumes images are the same size
void debug_image_overlap(Image* first, Image* second, const char* filename) {
	Image* overlap = image_blank_copy(first);

	for (int x = 0; x < image_width(overlap); x++) {
		for (int y = 0; y < image_height(overlap); y++) {
			Pixel& pixel = image_get_pixel(overlap, x, y);

			pixel.Red   = image_get_pixel_intensity(first, x, y);
			pixel.Green = image_get_pixel_intensity(second, x, y);
			pixel.Blue  = 255;
		}
	}

	image_to_file(overlap, filename);
	free_image(overlap);
}
