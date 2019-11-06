#include "vector.h"
#include <stdlib.h>
#include <assert.h> /* assert()*/

static void _resize(vector* vec, size_t capacity);

vector construct() {
  vector vec = {NULL, 0, INITIAL_CAPACITY};
  int* data = malloc(INITIAL_CAPACITY * sizeof(int));
  vec.data = data;

  return vec;
}


size_t size(vector* vec) {
  return vec->size;
}

size_t capacity(vector* vec) {
  return vec->capacity;
}

int is_empty(vector* vec) {
  return vec->size == 0;
}

void push(vector* vec, int i) {
  *(vec->data + vec->size) = i;
  vec->size += 1;
  int unused = vec->capacity - vec->size;
  if (unused < vec->size) {
    size_t new_cap = 2 * vec->size;
    _resize(vec, new_cap);
  }
}

static void _resize(vector* vec, size_t capacity) {
  assert(vec->data != NULL);
  int* p = realloc(vec->data, capacity * sizeof(int));
  vec->data = p;
  vec->capacity = capacity;
}


int destruct(vector* vec) {
  free(vec->data);
}

int at(vector* vec, int i) {
  int pos = (i >= 0) ? i : -i;
  if (pos >= vec->size) {
    return INDEX_OUT_OF_BOUND;
  }

  return *(vec->data + pos);
}

