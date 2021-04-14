#ifndef MATRIX_H
#define MATRIX_H

#include "row.h"

typedef struct matrix_s matrix_t;

matrix_t* matrix_make(int row_count, int col_count);
void matrix_free(matrix_t* matrix);
matrix_t* matrix_copy(matrix_t* matrix);
int matrix_countrows(matrix_t* matrix);
int matrix_countcols(matrix_t* matrix);
void matrix_print(matrix_t* matrix);
void matrix_println(matrix_t* matrix);
void matrix_pretty_print(matrix_t* matrix);
void matrix_pretty_println(matrix_t* matrix);
row_t* matrix_getrow(matrix_t* matrix, int row);
double matrix_get(matrix_t* matrix, int row, int col);
void matrix_swap(matrix_t* matrix, int row1, int row2);
bool matrix_fill_from_str_array(matrix_t* matrix, const char** str_array, int count);
bool matrix_fill_from_file(matrix_t* matrix, FILE* file);

#endif // MATRIX_H
