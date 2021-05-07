#include <stdlib.h>
#include <memory.h>

#include "matrix.h"
#include "math_utils.h"

struct matrix_s {
    row_t** rows;
    int count;
};

matrix_t* matrix_make(int row_count, int col_count) {
    if (row_count < 1 || col_count < 1) {
        return NULL;
    }
    matrix_t* matrix = malloc(sizeof(matrix_t));
    if (!matrix) {
        return NULL;
    }
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
    int         row_count = matrix_row_count(matrix);
    int         col_count = matrix_col_count(matrix);
    matrix_t*   copy = matrix_make(row_count, col_count);

    for (int i = 0; i < row_count; i++) {
        row_t* current = matrix_get_row(copy, i);
        row_t* value = matrix_get_row(matrix, i);
        row_assign(current, value);
    }

    return copy;
}

int matrix_row_count(matrix_t* matrix) {
    return matrix->count;
}

int matrix_col_count(matrix_t* matrix) {
    return row_count(matrix->rows[0]);
}

void matrix_print(matrix_t* matrix) {
    int row_count = matrix_row_count(matrix);
    for (int i = 0; i < row_count; i++) {
        row_print(matrix_get_row(matrix, i));
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
    int row_count = matrix_row_count(matrix);
    for (int i = 0; i < row_count; i++) {
        row_pretty_print(matrix_get_row(matrix, i));
        if (i != row_count - 1) {
            putchar('\n');
        }
    }
}

void matrix_pretty_println(matrix_t* matrix) {
    matrix_pretty_print(matrix);
    putchar('\n');
}

row_t* matrix_get_row(matrix_t* matrix, int row) {
    return matrix->rows[row];
}

double matrix_get(matrix_t* matrix, int row, int col) {
    return row_get(matrix_get_row(matrix, row), col);
}

void matrix_set(matrix_t* matrix, int row, int col, double value) {
    row_t* p_row = matrix_get_row(matrix, row);
    row_set(p_row, col, value);
}

void matrix_assign_row(matrix_t* matrix, int row, row_t* value) {
    row_t* p_row = matrix_get_row(matrix, row);
    row_assign(p_row, value);
}

void matrix_assign(matrix_t* left, matrix_t* right) {
    int row_count = min(matrix_row_count(left), matrix_row_count(right));
    int col_count = min(matrix_col_count(left), matrix_col_count(right));
    for (int i = 0; i < row_count; i++) {
        for (int j = 0; j < col_count; j++) {
            matrix_set(left, i, j, matrix_get(right, i, j));
        }
    }
}

void matrix_swap_rows(matrix_t* matrix, int row1, int row2) {
    row_t* temp = matrix->rows[row1];
    matrix->rows[row1] = matrix->rows[row2];
    matrix->rows[row2] = temp;
}

bool matrix_fill_from_str_array(matrix_t* matrix, const char** str_array, int count) {
    if (count != matrix_row_count(matrix)) {
        return false;
    }

    for (int i = 0; i < count; i++) {
        if (!row_fill_from_str(matrix_get_row(matrix, i), str_array[i])) {
            return false;
        }
    }

    return true;
}

bool matrix_fill_from_file(matrix_t* matrix, FILE* file) {
    if (!file) {
        return false;
    }

    int row_count = matrix_row_count(matrix);
    for (int i = 0; i < row_count; i++) {
        row_t* row = matrix_get_row(matrix, i);
        bool result = row_fill_from_file(row, file);
        if (!result || (feof(file) && i < row_count - 1)) {
            return false;
        }
    }

    return true;
}

void matrix_fill_sequentially(matrix_t* matrix) {
    for (int i = 0; i < matrix_row_count(matrix); i++) {
        for (int j = 0; j < matrix_col_count(matrix); j++) {
            matrix_set(matrix, i, j, (double)((j + 1) * (i + 1)));
        }
    }
}