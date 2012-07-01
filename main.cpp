#include "src/image.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Usage: run <input_filename> <output_filename>";
		cout << endl << endl;
		return 1;
	}

	// declare and read the bitmap
	Image* image = image_from_file(argv[1]);
	int height   = image_height(image);
	int width    = image_width(image);


	// convert each pixel to grayscale using RGB->YUV
	for (int j = 0; j < height; j++) {
		for (int i=0; i < width; i++) {
			Pixel &pixel = image_get_pixel(image, i, j);
			Byte mix = (Byte)floor(0.299*pixel.Red + 0.587*pixel.Green + 0.114*pixel.Blue);

			pixel.Red   = mix;
			pixel.Green = mix;
			pixel.Blue  = mix;
		}
	}

	ensure_grayscale_color_table(image);
	image_to_file(image, argv[2]);

	free_image(image);

	return 0;
}
