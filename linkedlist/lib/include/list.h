#ifndef VECTOR_LIB_H__
#define VECTOR_LIB_H__
#include <stdlib.h>


typedef struct _list_node linked_list;

typedef void* value;

enum result {SUCCESS,
             INDEX_OUT_OF_BOUND,
             INSUFFICIENT_MEMORY,
             NO_VALUE
             };

typedef enum result error;

struct _list_node {
  value data;
  size_t size;
  struct _list_node* next;
};

linked_list* new_linked_list();

size_t size(linked_list* l);

int empty(linked_list* l);

error value_at(linked_list* l, size_t i, value* v);

error push_front(linked_list* l, value v);

error pop_front(linked_list* l, value* v);

error push_back(linked_list* l, value v);

error pop_back(linked_list* l, value* v);

error front(linked_list* l, value* v);

error back(linked_list* l, value* v);

error insert(linked_list* l, size_t i, value v);

void erase(linked_list* l, size_t i);

value value_n_from_end(linked_list* l, size_t n);

void reverse(linked_list* l);

int remove_value(value v);

#endif
