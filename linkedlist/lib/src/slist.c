#include "slist.h"
#include <stdbool.h>
#include <stdlib.h>

size_t size(ListEntry* l) {
  size_t ret = 0;

  while(l) {
    ret++;
    l = l->next;
  }

  return ret;
}

bool empty(ListEntry* l) {
  return (size(l) == 0 ? true : false);
}

Value value_at(ListEntry* l, size_t i) {

  while(i--) {

    if (l == NULL) {
      return VALUE_NULL;
    }

    l = l->next;

  }

  return l->data;
}

ListEntry* push_front(ListEntry** l, Value v) {
  ListEntry* entry;

  entry = (ListEntry* ) malloc(sizeof(ListEntry));

  if (entry == NULL) {
    return NULL;
  }

  entry->data = v;
  entry->next = *l;

  *l = entry;

  return entry;
}

Value pop_front(ListEntry** l) {

  if (*l == NULL) {
    return VALUE_NULL;
  }

  ListEntry* entry;
  entry = *l;

  Value ret;
  ret = (*l)->data;

  *l = (*l)->next;
  free(entry);

  return ret;
}

ListEntry* push_back(ListEntry** l, Value v) {

  ListEntry* entry;
  entry = (ListEntry* ) malloc(sizeof(ListEntry));

  if (entry == NULL) {
    return NULL;
  }
  entry->data = v;
  entry->next = NULL;


  if (*l == NULL) {
    *l = entry;
    return entry;
  }

  while(*l) {
    l = &((*l)->next);
  }

  *l = entry;
  return entry;
}

Value pop_back(ListEntry** l) {

  Value ret;
  ret = VALUE_NULL;

  // 零个元素
  if (*l == NULL) {
    return ret;
  }

  while((*l)->next) {
    l= &((*l)->next);
  }

  ret = (*l)->data;
  free(*l);
  *l = NULL;

  return ret;
}

Value front(ListEntry* l) {
  if (l == NULL) {
    return VALUE_NULL;
  }

  return l->data;
}

Value back(ListEntry* l) {
  if (l == NULL) {
    return VALUE_NULL;
  }

  while(l->next) {
    l = l->next;
  }

  return l->data;
}

ListEntry* insert(ListEntry** l, size_t i, Value v) {
  if (i > size(*l)) {
    return NULL;
  }

  ListEntry* entry;

  entry = (ListEntry* ) malloc(sizeof(ListEntry));
  if (entry == NULL) {
    return NULL;
  }

  entry->data = v;


  while(i--) {
    l = &((*l)->next);
  }

  entry->next = *l;
  *l = entry;
}

Value erase(ListEntry** l, size_t i) {
  if (i >= size(*l)) {
    return VALUE_NULL;
  }

  while(i--) {
    l = &((*l)->next);
  }

  ListEntry* inode;
  inode = *l;

  *l = inode ->next;
  free(inode);
}

Value value_n_from_end(ListEntry* l, size_t n) {

  if (n == 0) {
    return VALUE_NULL;
  }

  ListEntry *fast, *slow;
  fast = slow = l;

  while(fast) {
    fast = fast->next;

    if (n != 0) {
      n--;
    } else {
      slow = slow->next;
    }
  }

  return slow->data;
}

void reverse(ListEntry** l) {

  ListEntry* previous = NULL;
  ListEntry* current;

  current = *l;

  while(current) {
    ListEntry* next = current->next;
    current->next = previous;
    previous = current;
    current = next;
  }

  *l = previous;
}

size_t remove_value(ListEntry** l, Value v, ValueEqualFunc func) {

  size_t removed_counter = 0;

  while(*l) {
    if (func((*l)->data, v)) {
      ListEntry* tmp;
      tmp = *l;
      *l = (*l)->next;
      free(tmp);
      removed_counter++;
    } else {
      l = &((*l)->next);
    }
  }

  return removed_counter;
}

void destruct(ListEntry** l) {

  if (*l == NULL) {
    return;
  }

  ListEntry *next;
  while(*l) {
    next = (*l)->next;
    free(*l);
    *l = next;
  }
}
