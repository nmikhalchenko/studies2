#ifndef M_INPUT_H
#define M_INPUT_H

#include <stdbool.h>

#include "matrix.h"

#define DEFAULT_MATRIX_FILENAME ("matrix.txt")

bool m_try_read(const char* filename);

#endif // M_INPUT_H