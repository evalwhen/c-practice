#ifndef VECTOR_LIB_H__
#define VECTOR_LIB_H__
#include <stdlib.h>

#define INITIAL_CAPACITY 16

typedef struct {
  int* data;
  size_t size;
  size_t capacity;
} vector;

typedef enum {SUCCESS, INDEX_OUT_OF_BOUND} error;

vector construct();
size_t size(vector* vec);
size_t capacity(vector* vec);
int is_empty(vector* vec);
int at(vector* vec, int i);
void push(vector* vec, int i);
int insert(vector* vec, int i, int ele);
void prepend(vector* vec, int ele);
int pop(vector* vec);
int delete(vector* vec, int i);
int rem(vector* vec, int ele);
int find(vector* vec, int ele);

int destruct(vector* vec);
/* int resize(vector* vec, int new_cap); */

#endif
