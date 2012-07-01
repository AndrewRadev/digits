#include "image.h"

Image* image_from_file(const char *filename) {
	Image* image = new Image;
	image->ReadFromFile(filename);

	return image;
}

void free_image(Image* image) {
	delete image;
}
