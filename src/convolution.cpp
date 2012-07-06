#include "dbg.h"
#include <cassert>
#include "convolution.h"

Image* image_convolution(Image* image, Matrix* matrix) {
	int height     = image_height(image);
	int width      = image_width(image);
	int new_height = height - matrix->row_count;
	int new_width  = width - matrix->column_count;

	Image* output = image_blank_copy(image, new_width, new_height);

	int top    =	      (matrix->row_count    / 2);
	int bottom = height - (matrix->row_count    / 2 + matrix->row_count % 2);
	int left   =	      (matrix->column_count / 2);
	int right  = width -  (matrix->column_count / 2 + matrix->column_count % 2);

	for (int i = top; i < bottom ; i++) {
		for (int j = left; j < right; j++) {
			assert(i < image_height(image));
			assert(j < image_width(image));
			assert(i - top < image_height(output));
			assert(j - left < image_width(output));
			assert(i - top >= 0);
			assert(j - left >= 0);

			int value = pixel_convolution(image, matrix, i, j);
			image_set_pixel_intensity(output, j - left, i - top, value);
		}
	}

	return output;
}

int pixel_convolution(Image* image, Matrix* matrix, int top, int left) {
	int value       = 0;
	int top_offset  = top - matrix->row_count / 2;
	int left_offset = left - matrix->column_count / 2;

	for (int i = 0; i < matrix->row_count; i++) {
		for (int j = 0; j < matrix->column_count; j++) {
			assert(i + top_offset < image_height(image));
			assert(j + left_offset < image_width(image));
			assert(i + top_offset >= 0);
			assert(j + left_offset >= 0);

			int matrix_value = matrix->data[i][j] / 255.0;
			int pixel_value  = image_get_pixel_intensity(image, left_offset + j, top_offset + i) / 255.0;

			value += matrix_value * pixel_value;
		}
	}

	return (int)((value / (float)(matrix->row_count * matrix->column_count)) * 255.0);;
}
