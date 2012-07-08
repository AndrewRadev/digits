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

Pixel& image_get_pixel(Image* image, int x, int y) {
	return *(image->operator()(x, y));
}

// This assumes that the image is already grayscale
int image_get_pixel_intensity(Image* image, int x, int y) {
	return image_get_pixel(image, x, y).Blue;
}

void image_set_pixel_intensity(Image* image, int x, int y, int intensity) {
	Pixel& pixel = image_get_pixel(image, x, y);

	pixel.Red   = intensity;
	pixel.Green = intensity;
	pixel.Blue  = intensity;
}

Image* image_invert(Image* image) {
	for (int x = 0; x < image_width(image); x++) {
		for (int y = 0; y < image_height(image); y++) {
			Pixel& pixel = image_get_pixel(image, x, y);

			pixel.Red   = 255 - pixel.Red;
			pixel.Green = 255 - pixel.Green;
			pixel.Blue  = 255 - pixel.Blue;
		}
	}

	return image;
}

int image_max_intensity(Image* image) {
	int max = 0;

	for (int x = 0; x < image_width(image); x++) {
		for (int y = 0; y < image_height(image); y++) {
			int value = image_get_pixel_intensity(image, x, y);

			if (max < value) {
				max = value;
			}
		}
	}

	return max;
}

void image_to_file(Image* image, const char* filename) {
	image->WriteToFile(filename);
}

Matrix* image_to_intensity_matrix(Image* image) {
	Matrix* matrix = new_matrix(image->TellHeight(), image->TellWidth());

	for (int y = 0; y < matrix->row_count; y++) {
		for (int x = 0; x < matrix->column_count; x++) {
			matrix->data[y][x] = image_get_pixel_intensity(image, x, y);
		}
	}

	return matrix;
}
