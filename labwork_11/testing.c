#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "testing.h"

typedef bool (*test_func_t)(void);

// File to write tests in:
#include "tests.c"

static test_func_t g_tests[] = {
    t_eq_matrix_eq_count,
    t_eq_matrix_unknown_count,
    t_eq_matrix_is_square,
};

static test_results_t test_results_make(void) {
    test_results_t r;
    r.test_count = sizeof(g_tests) / sizeof(test_func_t);
    r.passed_count = 0;
    r.failed_list = NULL;
    r.failed_count = 0;
    return r;
}

void test_results_free(test_results_t r) {
    if (r.failed_list) {
        free(r.failed_list);
    }
}

test_results_t tests_run_r(void) {
    test_results_t r = test_results_make();

    for (int i = 0; i < r.test_count; i++) {
        bool result = g_tests[i]();
        if (result) {
            r.passed_count++;
        } else {
            if (!r.failed_list) {
                r.failed_list = malloc(sizeof(int) * r.test_count);
            }
            r.failed_list[r.failed_count++] = i;
        }
    }

    return r;
}

void tests_run(void) {
    puts("--- Running tests ---");

    test_results_t r = tests_run_r();

    printf("%12s: %5d\n", "Total", r.test_count);
    printf("%12s: %5d\n", "Passed", r.passed_count);
    printf("%12s: %5d\n", "Failed", r.failed_count);
    if (r.failed_list) {
        puts("- Failed tests -");
        for (int i = 0; i < r.failed_count; i++) {
            printf("  %d;\n", i + 1);
        }
    }

    test_results_free(r);

    puts("--- Tests over ---");
}