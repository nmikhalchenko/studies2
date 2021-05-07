#ifndef TESTING_H
#define TESTING_H

typedef struct test_results_s {
    int test_count;
    int passed_count;
    int* failed_list;
    int failed_count;

} test_results_t;

void test_results_free(test_results_t r);
test_results_t tests_run_r(void);
void tests_run(void);

#endif // TESTING_H
