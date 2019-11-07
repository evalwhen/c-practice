#ifndef VECTOR_LIB_H__
#define VECTOR_LIB_H__
#include <stdlib.h>
#include <stdbool.h>


typedef struct _list_node linked_list;

typedef void* value;

enum result {SUCCESS,
             INDEX_OUT_OF_BOUND,
             INSUFFICIENT_MEMORY,
             NO_VALUE
             };

typedef enum result error;

struct _list_node {
  value value;
  size_t size;
  struct _list_node* next;
};

linked_list* new_linked_list();

size_t size(linked_list* l);

bool empty(linked_list* l);

error value_at(linked_list* l, size_t i, value* v);

error push_front(linked_list* l, value v);

error pop_front(linked_list* l, value* v);

error push_back(linked_list* l, value v);

error pop_back(linked_list* l, value* v);

value front(linked_list* l);

value back(linked_list* l);

error insert(linked_list* l, size_t i, value v);

error erase(linked_list* l, size_t i);

error value_n_from_end(linked_list* l, size_t n, value* v);

void reverse(linked_list* l);

int remove_value(value v);

void destruct(linked_list* l);

#endif
