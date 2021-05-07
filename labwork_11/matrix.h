#ifndef MATRIX_H
#define MATRIX_H

#include "row.h"

typedef struct matrix_s matrix_t;

matrix_t*   matrix_make(int row_count, int col_count);
void        matrix_free(matrix_t* matrix);
matrix_t*   matrix_copy(matrix_t* matrix);
int         matrix_row_count(matrix_t* matrix);
int         matrix_col_count(matrix_t* matrix);
void        matrix_print(matrix_t* matrix);
void        matrix_println(matrix_t* matrix);
void        matrix_pretty_print(matrix_t* matrix);
void        matrix_pretty_println(matrix_t* matrix);
row_t*      matrix_get_row(matrix_t* matrix, int row);
double      matrix_get(matrix_t* matrix, int row, int col);
void        matrix_set(matrix_t* matrix, int row, int col, double value);
void        matrix_assign_row(matrix_t* matrix, int row, row_t* value);
void        matrix_assign(matrix_t* left, matrix_t* right);
void        matrix_swap_rows(matrix_t* matrix, int row1, int row2);
bool        matrix_fill_from_str_array(matrix_t* matrix, const char** str_array, int count);
bool        matrix_fill_from_file(matrix_t* matrix, FILE* file);
void        matrix_fill_sequentially(matrix_t* matrix);

#endif // MATRIX_H
