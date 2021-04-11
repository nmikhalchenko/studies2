#include <stdlib.h>

#include "random_funcs.h"

// Generic macro to get a whole number of any size
#define RANDOM_INTEGRAL(min, max) (rand() % (max - min) + min)
// Generic macro to get a real number of any size
#define RANDOM_FLOAT(min, max) (min + rand() / (RAND_MAX / (max - min)))

char random_char(char min, char max) {
    return RANDOM_INTEGRAL(min, max);
}

int random_int(int min, int max) {
    return RANDOM_INTEGRAL(min, max);
}

long random_long(long min, long max) {
    return RANDOM_INTEGRAL(min, max);
}

float random_float(float min, float max) {
    return RANDOM_FLOAT(min, max);
}

double random_double(double min, double max) {
    return RANDOM_FLOAT(min, max);
}