#include "image.h"

Image* image_from_file(const char *filename) {
	Image* image = new Image;
	image->ReadFromFile(filename);

	return image;
}

Image* image_blank_copy(Image* image) {
	Image* copy = new Image;
	copy->SetSize(image->TellWidth(), image->TellHeight());
	copy->SetBitDepth(image->TellBitDepth());

	return copy;
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

// This assumes that the image is already grayscale
int image_get_pixel_intensity(Image* image, int i, int j) {
	return image_get_pixel(image, i, j).Blue;
}

void image_set_pixel_intensity(Image* image, int i, int j, int intensity) {
	Pixel& pixel = image_get_pixel(image, i, j);

	pixel.Red   = intensity;
	pixel.Green = intensity;
	pixel.Blue  = intensity;
}

void image_to_file(Image* image, const char* filename) {
	image->WriteToFile(filename);
}
