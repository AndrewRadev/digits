#ifndef MATRIX_H
#define MATRIX_H

typedef struct Matrix {
	int row_count;
	int column_count;

	int** data;
} Matrix;

Matrix* new_matrix(int row_count, int column_count);
void free_matrix(Matrix* matrix);

#endif
