/*
    This file must not be included anywhere else and is only for storing tests.
    The test mechanism is implemented in testing.c and testing.h
*/

#include <stdlib.h>

#include "equation.h"

static bool t_eq_matrix_eq_count(void) {
    matrix_t* matrix = matrix_make(3, 4);
    matrix_fill_sequentially(matrix);
    int eq_count = eq_matrix_eq_count(matrix);
    bool result = eq_count == 3;
    matrix_free(matrix);
    return result;
}

static bool t_eq_matrix_unknown_count(void) {
    matrix_t* matrix = matrix_make(3, 4);
    matrix_fill_sequentially(matrix);
    int unknown_count = eq_matrix_unknown_count(matrix);
    bool result = unknown_count == 3;
    matrix_free(matrix);
    return result;
}

static bool t_eq_matrix_is_square(void) {
    matrix_t* matrix = matrix_make(3, 4);
    matrix_fill_sequentially(matrix);
    bool result = eq_matrix_is_square(matrix);
    matrix_free(matrix);
    return result;
}