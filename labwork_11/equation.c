#include "equation.h"

int eq_matrix_eq_count(matrix_t* matrix) {
    return matrix_row_count(matrix);
}

int eq_matrix_unknown_count(matrix_t* matrix) {
    return matrix_col_count(matrix) - 1;
}

bool eq_matrix_is_square(matrix_t* matrix) {
    int eq_count = eq_matrix_eq_count(matrix);
    int unknown_count = eq_matrix_unknown_count(matrix);
    return eq_count == unknown_count;
}

// Combines extra rows if the matrix has has more equations than unknowns, and vice versa.
// If matrix is already square, returns it instead.
// Returns NULL on failure
matrix_t* eq_matrix_make_square(matrix_t* matrix) {
    if (eq_matrix_is_square(matrix)) {
        return matrix;
    }

    int eq_count = eq_matrix_eq_count(matrix);
    int unknown_count = eq_matrix_unknown_count(matrix);
    // the dimensions of the to-be matrix
    int new_eq_count = eq_count;
    int new_unknown_count = unknown_count;
    
    // adjust until square
    bool eq_count_higher = false;
    while (new_eq_count < new_unknown_count) {
        new_eq_count++;
    }
    while (new_eq_count > new_unknown_count) {
        if (!eq_count_higher) {
            eq_count_higher = true;
        }
        new_unknown_count++;
    }

    matrix_t* new = matrix_make(new_eq_count, new_unknown_count + 1);
    matrix_assign(new, matrix);

    if (eq_count_higher) {
        row_t* row = matrix_get_row(matrix, eq_count - 1);
        for (int i = eq_count; i < new_eq_count; i++) {
            matrix_assign_row(new, i, row);
        }
    }

    return new;
}