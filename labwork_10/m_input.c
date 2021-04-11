#include <stdio.h>
#include <memory.h>

#include "m_input.h"

static bool m_try_read_row(FILE* file, double* output_buffer, int output_bufsize) {
    if (output_bufsize < COLS) {
        return false;
    }

    size_t assignment_count = fscanf(file, COLS_FORMAT, COLS_ADDRESSES(output_buffer));
    if (assignment_count != COLS) {
        return false;
    }

    return true;
}

bool m_try_read(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return false;
    }

    double output_buffer[ROWS][COLS];
    bool success = true;
    for (int i = 0; i < ROWS; i++) {
        success = m_try_read_row(file, output_buffer[i], COLS);
        if (!success) {
            break;
        }
    }
    fclose(file);

    if (success) {
        for (int i = 0; i < ROWS; i++) {
            memcpy(matrix[i], output_buffer[i], sizeof(double) * COLS);
        }
    }

    return success;
}