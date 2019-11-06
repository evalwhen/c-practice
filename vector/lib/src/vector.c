#include "vector.h"
#include <stdlib.h> /* molloc, realloc */
#include <assert.h> /* assert()*/

static void _resize(vector* vec);
static void _shrink(vector* vec);

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
  _resize(vec);
}

int insert(vector* vec, int i, int ele) {
  if (i < 0 || i > vec->size) {
    return INDEX_OUT_OF_BOUND;
  }

  int counter = vec->size - i;
  int* p = vec->data + vec->size;
  while(counter--) {
    *p = *(p - 1);
    p--;
  }
  *(vec->data + i) = ele;
  vec->size += 1;
  _resize(vec);

  return 0;
}

void prepend(vector* vec, int ele) {
  insert(vec, 0, ele);
}

int pop(vector* vec) {
  int val = *(vec->data + vec->size - 1);
  vec->size -= 1;
  _shrink(vec);

  return val;
}

int delete(vector* vec, int i) {

  //TODO: INDEX_OUT_OF_BOUND, 无法从返回值中区分是error 还是成功。
  if (i < 0 || i >= vec->size) {
    return INDEX_OUT_OF_BOUND;
  }

  int val = *(vec->data + i);
  for (; i < (vec->size - 1); i++) {
    *(vec->data + i) = *(vec->data + i + 1);
  }

  vec->size -= 1;

  _shrink(vec);

  return val;
}

int at(vector* vec, int i) {
  int pos = (i >= 0) ? i : (vec->size + i);
  if (pos >= vec->size) {
    return INDEX_OUT_OF_BOUND;
  }

  return *(vec->data + pos);
}


int find(vector* vec, int ele) {
  int index = -1;
  for(int i = 0; i < vec->size; i++) {
    int v = *(vec->data + i);
    if (v == ele) {
      index = i;
    }
  }

  return index;
}

static void _resize(vector* vec) {
  assert(vec->data != NULL);
  int unused = vec->capacity - vec->size;
  if (unused < vec->size) {
    int capacity = 2 * vec->size;
    int* p = realloc(vec->data, capacity * sizeof(int));
    vec->data = p;
    vec->capacity = capacity;
  }
}

static void _shrink(vector* vec) {
  assert(vec->data != NULL);
  // 如果发现 size 小于等于 实际占用内存的四分之一，那么将 capacity 降低到原来的一半。
  if (vec->size <= (vec->capacity / 4)) {
    size_t new_cap = vec->capacity / 2;
    int* p = realloc(vec->data,  new_cap * sizeof(int));
    vec->data = p;
    vec->capacity = new_cap;
  }
}

int destruct(vector* vec) {
  free(vec->data);
}
