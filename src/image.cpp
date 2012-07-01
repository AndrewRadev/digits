#include "image.h"

Image* image_from_file(const char *filename) {
	Image* image = new Image;
	image->ReadFromFile(filename);

	return image;
}

void free_image(Image* image) {
	delete image;
}

int image_height(Image* image) {
	return image->TellHeight();
}

int image_width(Image* image) {
	return image->TellWidth();
}

Pixel& image_get_pixel(Image* image, int i, int j) {
	return *(image->operator()(i, j));
}

void image_to_file(Image* image, const char* filename) {
	image->WriteToFile(filename);
}
