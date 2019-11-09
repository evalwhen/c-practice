#ifndef SLIST_LIB_H__
#define SLIST_LIB_H__
#include <stdlib.h>
#include <stdbool.h>


typedef struct _ListEntry ListEntry;

typedef void* Value;

typedef bool (*ValueEqualFunc)(Value a, Value b);

typedef ListEntry* LinkList;

#define VALUE_NULL ((void*) 0)

struct _ListEntry {
  Value data;
  ListEntry* next;
};

size_t size(ListEntry* l);

bool empty(ListEntry* l);

Value value_at(ListEntry* l, size_t i);

ListEntry* push_front(ListEntry** l, Value v);

Value pop_front(ListEntry** l);

ListEntry* push_back(ListEntry** l, Value v);

Value pop_back(ListEntry** l);

Value front(ListEntry* l);

Value back(ListEntry* l);

ListEntry* insert(ListEntry** l, size_t i, Value v);

Value erase(ListEntry** l, size_t i);

Value value_n_from_end(ListEntry* l, size_t n);

void reverse(ListEntry** l);

size_t remove_value(ListEntry** l, Value v, ValueEqualFunc func);

void destruct(ListEntry** l);

#endif
