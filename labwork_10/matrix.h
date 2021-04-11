#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdbool.h>

#define ROWS (3)
#define COLS (4)
#define COLS_FORMAT ("%lg %lg %lg %lg")
#define COLS_ADDRESSES(bufname) bufname, bufname + 1, bufname + 2, bufname + 3
#define X_COUNT (COLS - 1)

extern double* matrix[ROWS];

#endif // CONSTANTS_H