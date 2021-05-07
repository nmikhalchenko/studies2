#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "row.h"
#include "math_utils.h"

struct row_s {
    double* cols;
    int count;
};

row_t* row_make(int col_count) {
    row_t* row = malloc(sizeof(row_t));
    row->count = col_count;
    row->cols = calloc(col_count, sizeof(double));
    return row;
}

void row_free(row_t* row) {
    if (row) {
        if (row->cols) {
            free(row->cols);
        }
        free(row);
    }
}

row_t* row_copy(row_t* row) {
    int     count = row_count(row);
    row_t*  copy = row_make(count);

    for (int i = 0; i < count; i++) {
        double current = row_get(row, i);
        row_set(copy, i, current);
    }

    return copy;
}

int row_count(row_t* row) {
    return row->count;
}

double row_get(row_t* row, int col) {
    return row->cols[col];
}

void row_set(row_t* row, int col, double value) {
    row->cols[col] = value;
}

void row_assign(row_t* left, row_t* right) {
    int count = min(row_count(left), row_count(right));
    for (int i = 0; i < count; i++) {
        row_set(left, i, row_get(right, i));
    }
}

void row_print(row_t* row) {
    for (int i = 0; i < row->count; i++) {
        printf("%5lg", row->cols[i]);
        if (i != row->count - 1) {
            printf(" ");
        }
    }
}

void row_println(row_t* row) {
    row_print(row);
    putchar('\n');
}

void row_pretty_print(row_t* row) {
    printf("{ ");
    row_print(row);
    printf(" }");
}

void row_pretty_println(row_t* row) {
    row_pretty_print(row);
    putchar('\n');
}

void row_add(row_t* row, row_t* added_row, double multiplier) {
    for (int i = 0; i < row->count; i++) {
        row->cols[i] += added_row->cols[i] * multiplier;
    }
}

void row_subtract(row_t* row, row_t* subtracted_row, double multiplier) {
    for (int i = 0; i < row->count; i++) {
        row->cols[i] -= subtracted_row->cols[i] * multiplier;
    }
}

void row_multiply(row_t* row, double multiplier) {
    for (int i = 0; i < row->count; i++) {
        row->cols[i] *= multiplier;
    }
}

void row_divide(row_t* row, double divisor) {
    for (int i = 0; i < row->count; i++) {
        row->cols[i] /= divisor;
    }
}

int row_estimate_str_length(row_t* row) {
    return row_count(row) * 32;
}

static bool is_numeric_char(char c) {
    return isdigit(c) || c == '-' || c == '.';
}

bool row_fill_from_str(row_t* row, const char* str) {
    int     length = strlen(str);
    char    buf[32];
    int     top = 0;
    int     col = 0;
    char    c = '\0';
    char    last = '\0';

    buf[0] = '\0';

    for (int i = 0; i <= length; i++) {
        c = (i != length) ? str[i] : '\0';
        if (i == length || (!is_numeric_char(c) && is_numeric_char(last))) {
            if (col >= row_count(row)) {
                break;
            }
            row_set(row, col, strtod(buf, NULL));
            top = 0;
            col++;
        } else if (is_numeric_char(c)) {
            buf[top++] = c;
        }
        buf[top] = '\0';
        last = c;
    }
    return true;
}

bool row_fill_from_file(row_t* row, FILE* file) {
    if (!file) {
        return false;
    }

    int bufsize = row_estimate_str_length(row);
    char* buffer = malloc(bufsize);

    buffer[0] = '\0';
    if (!fgets(buffer, bufsize, file) && feof(file)) {
        rewind(file);
        clearerr(file);
        return false;
    } else if (ferror(file)) {
        buffer[0] = '\0';
        return false;
    }

    return row_fill_from_str(row, buffer);
}
