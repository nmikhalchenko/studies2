// Вариант 6

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"
#include "m_input.h"

void print_row_p(double* row) {
    printf("| %-11lg %-11lg %-11lg | %-11lg |\n", row[0], row[1], row[2], row[3]);
}

void print_row(int row) {
    print_row_p(matrix[row]);
}

void print_matrix(void) {
    static const char* divider = "+-------------------------------------+-------------+";
    puts(divider);
    for (int i = 0; i < ROWS; i++) {
        print_row(i);
    }
    puts(divider);
}

bool is_in_range(int row, int col) {
    bool row_in_range = (row >= 0 && row < ROWS);
    bool col_in_range = (col >= 0 && col < COLS);
    return row_in_range && col_in_range;
}

void row_add(int src_row, int dest_row, double multiplier) {
    for (int i = 0; i < COLS; i++) {
        matrix[dest_row][i] += (matrix[src_row][i] * multiplier);
    }
}

void row_subtract(int src_row, int dest_row, double multiplier) {
    for (int i = 0; i < COLS; i++) {
        matrix[dest_row][i] -= (matrix[src_row][i] * multiplier);
    }
}

void row_multiply(int row, double multiplier) {
    for (int i = 0; i < COLS; i++) {
        matrix[row][i] *= multiplier;
    }
}

void row_divide(int row, double divisor) {
    for (int i = 0; i < COLS; i++) {
        matrix[row][i] /= divisor;
    }
}

void row_swap(int row_1, int row_2) {
    double* temp = matrix[row_2];
    matrix[row_2] = matrix[row_1];
    matrix[row_1] = temp;
}

int first_nonzero_p(double* row) {
    int result = 0;
    for (int i = 0; i < COLS; i++) {
        double current = row[i];
        if (current == 0.0) {
            result++;
        } else {
            break;
        }
    }
    return result;
}

int first_nonzero(int row) {
    return first_nonzero_p(matrix[row]);
}

int first_nonzero_bottom_row(void) {
    for (int i = ROWS - 1; i >= 0; i--) {
        int nonzero_index = first_nonzero(i);
        if (is_in_range(0, nonzero_index)) {
            return i;
        }
    }
    return -1;
}

int normalize_by_first_nonzero(int row) {
    int nonzero_index = first_nonzero(row);
    if (is_in_range(0, nonzero_index) && matrix[row][nonzero_index] != 1.0) {
        double divisor = matrix[row][nonzero_index];
        printf("Normalizing row %i by %lg:\n", row + 1, divisor);
        row_divide(row, divisor);
        print_matrix();
    }
    return nonzero_index;
}

void normalize_and_nullify_subsequent(int top_row) {
    int top_row_nonzero = normalize_by_first_nonzero(top_row);
    if (!is_in_range(0, top_row_nonzero)) {
        return;
    }

    for (int i = top_row + 1; i < ROWS; i++) {
        if (matrix[i][top_row_nonzero] == 0.0) {
            continue;
        }
        int nonzero_index = first_nonzero(i);
        if (is_in_range(0, nonzero_index)) {
            double multiplier = matrix[i][nonzero_index];
            printf("Subtracting row %i multiplied by %lg from row %i:\n", top_row + 1, multiplier, i + 1);
            row_subtract(top_row, i, multiplier);
            print_matrix();
        }
    }
}

static int row_zero_comparer(const void* left, const void* right) {
    double* l = *((double**)left);
    double* r = *((double**)right);

    int lnz = first_nonzero_p(l);
    int rnz = first_nonzero_p(r);

    return lnz - rnz;
}

void sort_rows_by_zeroes(void) {
    //puts("Sorting:");
    qsort(matrix, ROWS, sizeof(double*), row_zero_comparer);
    //print_matrix();
}

bool is_system_consistent(void) {
    for (int i = 0; i < ROWS; i++) {
        int nonzero_index = first_nonzero(i);
        if (nonzero_index == COLS - 1) {
            return false;
        }
    }
    return true;
}

bool is_system_square(void) {
    int bottom_row = first_nonzero_bottom_row();
    if (bottom_row < (ROWS - 1)) {
        return false;
    } else {
        return true;
    }
}

bool is_solvable(void) {
    return is_system_consistent() && is_system_square();
}

bool try_stepify(void) {
    for (int i = 0; i < ROWS; i++) {
        sort_rows_by_zeroes();
        normalize_and_nullify_subsequent(i);
        if (!is_solvable()) {
            return false;
        }
    }
    return true;
}

bool try_diagonalize(void) {
    if (!try_stepify()) {
        return false;
    }
    int bottom_row = first_nonzero_bottom_row();
    for (int j = COLS - 2; j >= 0; j--) {
        for (int i = bottom_row - 1; i >= 0; i--) {
            double multiplier = matrix[i][j];
            printf("Subtracting row %i multiplied by %lg from row %i:\n", bottom_row + 1, multiplier, i + 1);
            row_subtract(bottom_row, i, multiplier);
            print_matrix();
        }
        bottom_row--;
    }
    return true;
}

void calculate_x_array(double* x_output) {
    for (int i = 0; i < ROWS; i++) {
        x_output[i] = matrix[i][COLS - 1];
    }
}

int main(void) {
    bool file_read_succeeded = m_try_read(DEFAULT_MATRIX_FILENAME);
    if (!file_read_succeeded) {
        printf("Failed to read the matrix from file \"%s\". Using default matrix\n", DEFAULT_MATRIX_FILENAME);
    }

    bool solved = false;

    puts("Matrix:");
    print_matrix();
    if (is_solvable() && try_diagonalize()) {
        solved = true;
    }
    puts("");

    if (solved) {
        printf("Seeked values: ");

        double x_output[X_COUNT];
        for (int i = 0; i < ROWS; i++) {
            x_output[i] = matrix[i][COLS - 1];
        }

        printf("{ ");
        for (int i = 0; i < X_COUNT; i++) {
            printf("%lg ", x_output[i]);
        }
        printf("}\n\n");
    } else {
        puts("The program is unable to solve this system.");
    }
    puts("For more info refer to matrix.txt.");

    return 0;
}