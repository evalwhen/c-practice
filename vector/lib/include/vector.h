#ifndef VECTOR_LIB_H__
#define VECTOR_LIB_H__
#include <stdlib.h>

#define INITIAL_CAPACITY 16

typedef struct {
  int* data;
  size_t size;
  size_t capacity;
} vector;

vector new_vector();
size_t size(vector* vec);
size_t capacity(vector* vec);
int is_empty(vector* vec);
int at(vector* vec, int i);
void push(vector* vec, int i);
void insert(vector* vec, int i, int ele);
void prepend(vector* vec, int ele);
int pop(vector* vec);
void delete(vector* vec, int i);
int rem(vector* vec, int ele);
int find(vector* vec, int ele);

int free_vector(vector* vec);
/* int resize(vector* vec, int new_cap); */

#endif
