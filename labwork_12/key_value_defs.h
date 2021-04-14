#ifndef KEY_VALUE_DEFS_H
#define KEY_VALUE_DEFS_H

#include <stdbool.h>

#include "random_funcs.h"

/*
    What each option here means:
    1. The underlying type
    2. The min value (used for rand, iterating, etc.)
    3. The max value (same as above)
    4. The format specifier corresponding to the underlying type
    5. The underlying random function to use. DON'T FORGET to change it and don't touch anything else :D

    Only primitive types are supported. Structs could work but you can't increment them in loops.
*/

typedef char key_t;
#define KEY_MIN ('A')
#define KEY_MAX ('z')
#define KEY_FORMAT "%c"
static inline key_t random_key(void) {
    return random_char(KEY_MIN, KEY_MAX);
}

typedef int value_t;
#define VALUE_MIN (0)
#define VALUE_MAX (2048)
#define VALUE_FORMAT "%i"
static inline value_t random_value(void) {
    return random_int(VALUE_MIN, VALUE_MAX);
}

// BTW, static inlines are used so that I can define them in the header safely

#endif // KEY_VALUE_DEFS_H
