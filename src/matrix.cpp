#include <stdlib.h>

#include "matrix.h"

#include <cstdio>

Matrix* new_matrix(int row_count, int column_count) {
	Matrix* matrix       = (Matrix*)malloc(sizeof(Matrix));
	matrix->row_count    = row_count;
	matrix->column_count = column_count;
	matrix->data         = (int**)malloc(sizeof(int*) * row_count);

	for (int i = 0; i < row_count; i++) {
		matrix->data[i] = (int*)malloc(sizeof(int) * column_count);
	}

	return matrix;
}

void free_matrix(Matrix* matrix) {
	for (int i = 0; i < matrix->row_count; i++) {
		free(matrix->data[i]);
	}

	free(matrix->data);
	free(matrix);
}
