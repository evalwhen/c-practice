#include "vector.h"
#include <stdlib.h>

vector new_vector() {
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

