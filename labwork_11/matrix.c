#include "matrix.h"

#include <stdlib.h>
#include <memory.h>

struct matrix_s {
    row_t** rows;
    int count;
};

matrix_t* matrix_make(int row_count, int col_count) {
    matrix_t* matrix = malloc(sizeof(matrix_t));
    matrix->count = row_count;
    matrix->rows = calloc(row_count, sizeof(row_t*));
    for (int i = 0; i < row_count; i++) {
        matrix->rows[i] = row_make(col_count);
    }
    return matrix;
}

void matrix_free(matrix_t* matrix) {
    if (matrix && matrix->rows) {
        for (int i = 0; i < matrix->count; i++) {
            row_free(matrix->rows[i]);
        }
    }
}

matrix_t* matrix_copy(matrix_t* matrix) {
    int         row_count = matrix_countrows(matrix);
    int         col_count = matrix_countcols(matrix);
    matrix_t*   copy = matrix_make(row_count, col_count);

    for (int i = 0; i < row_count; i++) {
        row_t* current = matrix_getrow(copy, i);
        row_t* value = matrix_getrow(matrix, i);
        row_assign(current, value);
    }

    return copy;
}

int matrix_countrows(matrix_t* matrix) {
    return matrix->count;
}

int matrix_countcols(matrix_t* matrix) {
    return row_count(matrix->rows[0]);
}

void matrix_print(matrix_t* matrix) {
    int row_count = matrix_countrows(matrix);
    for (int i = 0; i < row_count; i++) {
        row_print(matrix_getrow(matrix, i));
        if (i != row_count - 1) {
            putchar('\n');
        }
    }
}

void matrix_println(matrix_t* matrix) {
    matrix_print(matrix);
    putchar('\n');
}

void matrix_pretty_print(matrix_t* matrix) {
    int row_count = matrix_countrows(matrix);
    for (int i = 0; i < row_count; i++) {
        row_pretty_print(matrix_getrow(matrix, i));
        if (i != row_count - 1) {
            putchar('\n');
        }
    }
}

void matrix_pretty_println(matrix_t* matrix) {
    matrix_pretty_print(matrix);
    putchar('\n');
}

row_t* matrix_getrow(matrix_t* matrix, int row) {
    return matrix->rows[row];
}

double matrix_get(matrix_t* matrix, int row, int col) {
    return row_get(matrix_getrow(matrix, row), col);
}

void matrix_swap(matrix_t* matrix, int row1, int row2) {
    row_t* temp = matrix->rows[row1];
    matrix->rows[row1] = matrix->rows[row2];
    matrix->rows[row2] = temp;
}

bool matrix_fill_from_str_array(matrix_t* matrix, const char** str_array, int count) {
    if (count != matrix_countrows(matrix)) {
        return false;
    }

    for (int i = 0; i < count; i++) {
        if (!row_fill_from_str(matrix_getrow(matrix, i), str_array[i])) {
            return false;
        }
    }

    return true;
}

bool matrix_fill_from_file(matrix_t* matrix, FILE* file) {
    if (!file) {
        return false;
    }

    int row_count = matrix_countrows(matrix);
    for (int i = 0; i < row_count; i++) {
        row_t* row = matrix_getrow(matrix, i);
        bool result = row_fill_from_file(row, file);
        if (!result || (feof(file) && i < row_count - 1)) {
            return false;
        }
    }

    return true;
}