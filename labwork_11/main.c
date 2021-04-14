// Вариант 6

/* Initial equation system:

    2.5x1 - 3.12x2 - 4.03x3 = -7.5
    0.61x1 + 0.71x2 -0.05x3 = 0.44
    -1.03x1 - 2.05x2 + 0.87x3 = -1.16
    
*/

#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

int main(void) {
    matrix_t* matrix = matrix_make(3, 4);
    FILE* file = fopen("matrix.txt", "r");
    if (matrix_fill_from_file(matrix, file)) {
        matrix_pretty_println(matrix);
    } else {
        puts("Failed to read from file");
    }
    return 0;
}