#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "random_funcs.h"

#define ARRAY_LENGTH (32)

double g_source_array[ARRAY_LENGTH];

void array_pretty_print(double* array, int length) {
    puts("\n-");
    for (int i = 0; i < length; i++) {
        printf("[%lg] ", array[i]);
    }
    puts("\n-\n");
}

typedef double (*comparer_t)(double left, double right);

double comparer(double left, double right) {
    if (left < 0 && right < 0) {
        return right - left;
    } else if (left == 0) {
        return 1;
    } else if (right == 0) {
        return -1;
    } else if (left < 0) {
        return 1;
    } else if (right < 0) {
        return -1;
    } else {
        return left - right;
    }
}

void insertion_sort(comparer_t comparer) {
    double current = 0.0;
    int location = 0;

    for (int i = 1; i < ARRAY_LENGTH; i++) {
        current = g_source_array[i];
        location = i - 1;
        while (location >= 0 && comparer(g_source_array[location], current) > 0) {
            g_source_array[location + 1] = g_source_array[location];
            location--;
        }
        g_source_array[location + 1] = current;
    }
}

int count_zeroes_after_sort(void) {
    int count = 0;
    for (int i = ARRAY_LENGTH - 1; i >= 0; i--) {
        if (g_source_array[i] == 0) {
            count++;
        } else {
            break;
        }
    }
    return count;
}

void copy_while_not_zero(double* dest_array, int dest_length) {
    int end = dest_length > ARRAY_LENGTH ? ARRAY_LENGTH : dest_length;
    for (int i = 0; i < end; i++) {
        double current = g_source_array[i];
        if (current == 0.0) {
            break;
        }
        dest_array[i] = current;
    }
}

typedef enum {
    FILL_MODE_UNKNOWN,
    FILL_MODE_RANDOM,
    FILL_MODE_FILE,

} fill_mode_t;

fill_mode_t translate_fill_mode(const char* input) {
    if (strcmp(input, "--random") == 0) {
        return FILL_MODE_RANDOM;
    } else if (strcmp(input, "--file") == 0) {
        return FILL_MODE_FILE;
    } else {
        return FILL_MODE_UNKNOWN;
    }
}

void source_fill_by_random(double min, double max) {
    srand(time(NULL));
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        g_source_array[i] = random_double(min, max);
    }
}

bool source_fill_by_file(void) {
    FILE* file = fopen("input.txt", "r");
    if (!file) {
        return false;
    }

    char    c;
    char    buffer[32];
    int     bufpos = 0;
    int     arrpos = 0;

    while (!feof(file) && arrpos < ARRAY_LENGTH) {
        c = fgetc(file);
        bool valid = isdigit(c) || c == '.' || c == '-';
        if (!valid || bufpos == sizeof(buffer) - 1) {
            g_source_array[arrpos++] = strtod(buffer, NULL);
            bufpos = 0;
        } else {
            buffer[bufpos++] = c;
        }
        buffer[bufpos] = '\0';
    }

    if (arrpos < ARRAY_LENGTH) {
        for (; arrpos < ARRAY_LENGTH; arrpos++) {
            g_source_array[arrpos] = 0.0;
        }
    }

    fclose(file);
    return true;
}

void source_fill_wrapper(int argc, const char** argv) {
    bool custom_args_provided = argc >= 2;
    bool default_behaviour = !custom_args_provided;

    if (custom_args_provided) {
        fill_mode_t mode = translate_fill_mode(argv[1]);
        switch (mode) {
            case FILL_MODE_RANDOM:
                if (argc >= 4) {
                    double min = strtod(argv[2], NULL);
                    double max = strtod(argv[3], NULL);
                    if (max < min) {
                        double temp = max;
                        max = min;
                        min = temp;
                    }
                    printf("Filling with random numbers from %lg to %lg\n", min, max);
                    source_fill_by_random(min, max);
                } else {
                    puts("No range provided");
                    default_behaviour = true;
                }
                break;
            case FILL_MODE_FILE:
                if (!source_fill_by_file()) {
                    puts("Failed to fill from file!");
                    default_behaviour = true;
                }
                break;
            default:
                printf("Unknown fill mode\n");
                break;
        }
    } else {
        puts("Tip: you can select how to fill the source array by providing one of the following: --random <min> <max>, --file");
    }

    if (default_behaviour) {
        puts("Filling with random numbers from -32.0 to 32.0");
        source_fill_by_random(-32.0, 32.0);
    }
}

int main(int argc, const char** argv) {
    source_fill_wrapper(argc, argv);

    puts("Source array:");
    array_pretty_print(g_source_array, ARRAY_LENGTH);

    insertion_sort(comparer);

    size_t dest_length = ARRAY_LENGTH - count_zeroes_after_sort();
    if (dest_length > 0) {
        double* dest_array = calloc(dest_length, sizeof(double));
        copy_while_not_zero(dest_array, dest_length);

        puts("Destination array:");
        array_pretty_print(dest_array, dest_length);

        free(dest_array);
    } else {
        printf("The destination array is empty - the source array had only zeroes!\n");
    }

    return 0;
}