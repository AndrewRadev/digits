#include "dbg.h"
#include "image.h"

Image* image_from_file(const char *filename) {
	Image* image = new Image;
	image->ReadFromFile(filename);

	return image;
}

Image* image_blank_copy(Image* image, int width, int height) {
	Image* copy = new Image;
	copy->SetSize(width, height);
	copy->SetBitDepth(image->TellBitDepth());

	return copy;
}

Image* image_blank_copy(Image* image) {
	return image_blank_copy(image, image->TellWidth(), image->TellHeight());
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

void image_invert(Image* image) {
	for (int i = 0; i < image_width(image); i++) {
		for (int j = 0; j < image_height(image); j++) {
			Pixel& pixel = image_get_pixel(image, i, j);

			pixel.Red   = 255 - pixel.Red;
			pixel.Green = 255 - pixel.Green;
			pixel.Blue  = 255 - pixel.Blue;
		}
	}
}

void image_to_file(Image* image, const char* filename) {
	image->WriteToFile(filename);
}

Matrix* image_to_intensity_matrix(Image* image) {
	Matrix* matrix = new_matrix(image->TellHeight(), image->TellWidth());

	for (int i = 0; i < matrix->row_count; i++) {
		for (int j = 0; j < matrix->column_count; j++) {
			matrix->data[i][j] = image_get_pixel_intensity(image, j, i);
		}
	}

	return matrix;
}
