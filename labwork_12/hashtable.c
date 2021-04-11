#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>

#include "hashtable.h"

typedef struct bucket_s {
    kv_t array[MAX_HASHTABLE_BUCKET_LENGTH];
    int count;

} bucket_t;

struct table_s {
    bucket_t* buckets[MAX_HASHTABLE_LENGTH];
    table_err_t error;
    hash_func_t hash_func;

} g_table = {
    {0},
    TABLE_ERR_NONE,
    modulo_hash_func
};

static hash_t get_hash(key_t key) {
    return g_table.hash_func(key);
}

// In case keys require to be compared in a special way, you can redefine it.
// Doubt that it's very useful though
static bool key_equals(key_t l, key_t r) {
    return l == r;
}

// Useless for now
/*
static bool value_equals(value_t l, value_t r) {
    return l == r;
}
*/

kv_t make_kv(key_t key, value_t value) {
    return (kv_t) { key, value };
}

static bucket_t* make_bucket(void) {
    bucket_t* bucket = malloc(sizeof(bucket_t));
    bucket->count = 0;
    return bucket;
}

// Useless for now
/*
static void free_bucket(bucket_t* bucket) {
    if (bucket) {
        free(bucket);
    }
}
*/

static kv_t* bucket_find_kv(bucket_t* bucket, key_t key) {
    for (int i = 0; i < bucket->count; i++) {
        key_t current_key = bucket->array[i].key;
        if (key_equals(key, current_key)) {
            return &bucket->array[i];
        }
    }
    return NULL;
}

static bool bucket_add_kv_unless_exists(bucket_t* bucket, kv_t kv) {
    if (bucket_find_kv(bucket, kv.key)) {
        return false;
    }
    if (bucket->count >= MAX_HASHTABLE_BUCKET_LENGTH) {
        g_table.error = TABLE_ERR_MAX_BUCKET_LENGTH_REACHED;
        return false;
    }

    bucket->array[bucket->count++] = kv;
    return true;
}

static bool bucket_add_kv_or_update(bucket_t* bucket, kv_t kv) {
    kv_t* found = bucket_find_kv(bucket, kv.key);
    if (found) {
        *found = kv;
        return false;
    } else {
        return bucket_add_kv_unless_exists(bucket, kv);
    }
}

void table_set_hash_func(hash_func_t hash_func) {
    g_table.hash_func = hash_func;
}

value_t* table_at(key_t key) {
    hash_t hash = get_hash(key);
    bucket_t* bucket = g_table.buckets[hash];
    if (!bucket) {
        return NULL;
    }

    kv_t* found = bucket_find_kv(bucket, key);
    if (found) {
        return &(found->value);
    } else {
        return NULL;
    }
}

bool table_contains(key_t key) {
    hash_t hash = get_hash(key);
    bucket_t* bucket = g_table.buckets[hash];
    if (!bucket) {
        return false;
    }

    kv_t* found = bucket_find_kv(bucket, key);
    if (found) {
        return true;
    } else {
        return false;
    }
}

bool table_add_or_update(kv_t kv) {
    hash_t hash = get_hash(kv.key);
    bucket_t** bucket_ptr = &(g_table.buckets[hash]);
    if (!*bucket_ptr) {
        *bucket_ptr = make_bucket();
    }
    return bucket_add_kv_or_update(*bucket_ptr, kv);
}

bool table_add_unless_exists(kv_t kv) {
    hash_t hash = get_hash(kv.key);
    bucket_t** bucket_ptr = &(g_table.buckets[hash]);
    if (*bucket_ptr) {
        return false;
    }
    *bucket_ptr = make_bucket();
    return bucket_add_kv_unless_exists(*bucket_ptr, kv);
}

table_err_t table_get_error_state(void) {
    return g_table.error;
}

void table_pretty_print(void) {
    printf("Table:\n");
    printf("%s : %i\n", "Error state", g_table.error);
    for (int i = 0; i < MAX_HASHTABLE_LENGTH; i++) {
        bucket_t* bucket = g_table.buckets[i];
        printf("%s %-3i : ", "Bucket", i);

        if (bucket) {
            for (int j = 0; j < bucket->count; j++) {
                printf("("KEY_FORMAT","VALUE_FORMAT") ", bucket->array[j].key, bucket->array[j].value);
            }
        } else {
            printf("NULL ");
        }
        puts("");
    }
}

hash_t modulo_hash_func(key_t key) {
    return key % MAX_HASHTABLE_LENGTH;
}

hash_t multiplicative_hash_func(key_t key) {
    static const float number = 0.618034f; // taken from the training manual
    float placeholder = 0.0f; // modff won't accept a NULL, gotta store the integral part somewhere
    // NOTE TO SELF: the cast truncates the thing, don't touch!!!
    return (int)(MAX_HASHTABLE_LENGTH * modff(key * number, &placeholder));
}