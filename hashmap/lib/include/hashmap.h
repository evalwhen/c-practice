#ifndef HASHMAP_LIB_H__
#define HASHMAP_LIB_H__

#include <stdbool.h>
#include <stdlib.h>
#include <inttypes.h>

typedef int MapKey;
typedef int MapValue;

typedef struct {
  MapKey key;
  MapValue value;
} MapEntry;

struct _hashMap {
  MapEntry* _data;
  size_t _capacity;
  size_t _size;
  size_t _prime;
  size_t _rand_a;
  size_t _rand_b;
};
typedef struct _hashMap* HashMap;

#define DEFAULT_CAPACITY  16

HashMap new_hashmap();

size_t entry_size(HashMap m);

void add(HashMap m, MapKey k, MapValue v);

MapValue get(HashMap m, MapKey k);

bool exists(HashMap m, MapKey k);

bool remove_key(HashMap m, MapKey k);

bool is_prime(int n);

int get_next_prime_larger_than(int n);

uint32_t randint (uint32_t a, uint32_t b);

void destruct_hashmap(HashMap h);

#endif
