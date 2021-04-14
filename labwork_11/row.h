#ifndef ROW_H
#define ROW_H

#include <stdbool.h>
#include <stdio.h>

typedef struct row_s row_t;

row_t* row_make(int col_count);
void row_free(row_t* row);
row_t* row_copy(row_t* row);
int row_count(row_t* row);
double row_get(row_t* row, int col);
void row_set(row_t* row, int col, double value);
void row_assign(row_t* left, row_t* right);
void row_print(row_t* row);
void row_println(row_t* row);
void row_pretty_print(row_t* row);
void row_pretty_println(row_t* row);
void row_add(row_t* row, row_t* added_row, double multiplier);
void row_subtract(row_t* row, row_t* subtracted_row, double multiplier);
void row_multiply(row_t* row, double multiplier);
void row_divide(row_t* row, double divisor);
int row_estimate_str_length(row_t* row);
bool row_fill_from_str(row_t* row, const char* str);
bool row_fill_from_file(row_t* row, FILE* file);

#endif // ROW_H
