#ifndef EQUATION_H
#define EQUATION_H

#include "matrix.h"

int eq_matrix_eq_count(matrix_t* matrix);
int eq_matrix_unknown_count(matrix_t* matrix);
bool eq_matrix_is_square(matrix_t* matrix);

#endif // EQUATION_H
