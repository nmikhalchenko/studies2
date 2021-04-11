// Вариант 6

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "hashtable.h"

int parse_int_arg(int index, int argc, const char** argv, int default_value) {
    int result = default_value;
    if (argc >= index + 1) {
        result = (int)strtol(argv[1], NULL, 0);
    }
    return result;
}

int add_random_elements(int count) {
    if (count < 0) {
        count = 0;
    }
    int actual_count = 0;
    for (int i = 0; i < count; i++) {
        kv_t kv = make_kv(random_key(), random_value());
        actual_count += table_add_or_update(kv) ? 1 : 0;
    }
    return actual_count;
}

double count_average_of_keys(void) {
    double average = 0;
    int count = 0;
    for (key_t i = KEY_MIN; i <= KEY_MAX; i++) {
        if (table_at(i)) {
            average += i;
            count++;
        }
    }
    return count == 0 ? 0 : average / count;
}

int count_values_higher_than(double threshold) {
    int higher_value_count = 0;
    for (key_t i = KEY_MIN; i < KEY_MAX; i++) {
        value_t* value = table_at(i);
        if (value) {
            if (*value > threshold) {
                higher_value_count++;
            }
        }
    }
    return higher_value_count;
}

int main(int argc, const char** argv) {
    srand(time(NULL)); // to init rand()
    table_set_hash_func(modulo_hash_func); // there are more hash funcs available in hashtable.h

    int elems_to_be_added = parse_int_arg(1, argc, argv, MAX_HASHTABLE_LENGTH);

    printf("Amount of elements to be added: %i\n", elems_to_be_added);
    if (argc < 2) {
        printf("Tip: you can change the amount of elements thrown in at the beginning with the first command line argument!\n");
    }

    int elems_added = add_random_elements(elems_to_be_added);

    table_pretty_print();

    if (elems_added > 0) {
        double average = count_average_of_keys();
        printf("The average of all occupied keys: %lg\n", average);

        int higher_value_count = count_values_higher_than(average);
        printf("Amount of values higher than the average of all occupied keys: %i\n", higher_value_count);
    }

    return 0;
}