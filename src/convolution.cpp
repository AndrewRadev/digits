#include "dbg.h"
#include <cassert>
#include "convolution.h"

Image* image_convolution(Image* image, Matrix* matrix) {
	int height     = image_height(image);
	int width      = image_width(image);
	int new_height = (height - matrix->row_count) + 1;
	int new_width  = (width - matrix->column_count) + 1;

	Image* output = image_blank_copy(image, new_width, new_height);

	int top    =	      (matrix->row_count    / 2);
	int bottom = height - (matrix->row_count    / 2 + matrix->row_count % 2) + 1;
	int left   =	      (matrix->column_count / 2);
	int right  = width -  (matrix->column_count / 2 + matrix->column_count % 2) + 1;

	for (int y = top; y < bottom ; y++) {
		for (int x = left; x < right; x++) {
			assert(y < image_height(image));
			assert(x < image_width(image));
			assert(y - top < image_height(output));
			assert(x - left < image_width(output));
			assert(y - top >= 0);
			assert(x - left >= 0);

			int value = pixel_convolution(image, matrix, y, x);
			image_set_pixel_intensity(output, x - left, y - top, value);
		}
	}

	return output;
}

int pixel_convolution(Image* image, Matrix* matrix, int top, int left) {
	float value     = 0;
	int top_offset  = top - matrix->row_count / 2;
	int left_offset = left - matrix->column_count / 2;

	for (int y = 0; y < matrix->row_count; y++) {
		for (int x = 0; x < matrix->column_count; x++) {
			assert(y + top_offset < image_height(image));
			assert(x + left_offset < image_width(image));
			assert(y + top_offset >= 0);
			assert(x + left_offset >= 0);

			int matrix_value = matrix->data[y][x] / 255.0;
			int pixel_value  = image_get_pixel_intensity(image, left_offset + x, top_offset + y) / 255.0;

			value += matrix_value * pixel_value;
		}
	}

	value /= (float)(matrix->row_count * matrix->column_count);

	assert(value >= 0);
	assert(value <= 1);

	return (int)(value * 255.0);
}
