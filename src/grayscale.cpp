#include "grayscale.h"

void convert_to_grayscale(Image* image) {
	int height = image_height(image);
	int width  = image_width(image);

	// convert each pixel to grayscale using RGB->YUV
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Pixel &pixel = image_get_pixel(image, x, y);
			Byte mix = (Byte)floor(0.299*pixel.Red + 0.587*pixel.Green + 0.114*pixel.Blue);

			pixel.Red   = mix;
			pixel.Green = mix;
			pixel.Blue  = mix;
		}
	}

	ensure_grayscale_color_table(image);
}

void ensure_grayscale_color_table(Image* image) {
	if (image->TellBitDepth() < 16) {
		CreateGrayscaleColorTable(*image);
	}
}
