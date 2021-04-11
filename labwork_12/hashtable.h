#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>

#include "key_value_defs.h"

typedef int hash_t;
typedef hash_t (*hash_func_t)(key_t);

typedef struct kv_s {
    key_t key;
    value_t value;

} kv_t;

#define MAX_HASHTABLE_LENGTH (32)
// How many keyvalues may be added to the same hash (bucket) before the whole thing breaks
#define MAX_HASHTABLE_BUCKET_LENGTH (32)

// All the possible ways the table can break
typedef enum {
    TABLE_ERR_NONE,
    TABLE_ERR_MAX_BUCKET_LENGTH_REACHED,

} table_err_t;

// Convenience function that makes a kv_t
kv_t make_kv(key_t key, value_t value);
// Sets the hash function used
void table_set_hash_func(hash_func_t hash_func);
// Yields the pointer to the value with the specified key, if it exists. NULL otherwise
value_t* table_at(key_t key);
// Checks whether the table has a keyvalue with the specified key
bool table_contains(key_t key);
// Returns false if an error occurs or if an existing keyvalue is updated, otherwise adds the keyvalue and true is returned
bool table_add_or_update(kv_t kv);
// Returns false if an error occurs or if the keyvalue already exists, otherwise adds the keyvalue and true is returned
bool table_add_unless_exists(kv_t kv);
// If this isn't zero, you're screwed
table_err_t table_get_error_state(void);
// Prints the whole table in a convenient way
void table_pretty_print(void);

hash_t modulo_hash_func(key_t key);
hash_t multiplicative_hash_func(key_t key);

#endif // HASHTABLE_H
