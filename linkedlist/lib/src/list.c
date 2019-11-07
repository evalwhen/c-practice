#include "list.h"
#include <stdlib.h>
#include <stdbool.h>

linked_list* new_linked_list() {

  linked_list* header;

  header = (linked_list*) malloc(sizeof(linked_list));

  if (header == NULL) {
    return NULL;
  }

  header->size = 0;
  header->next = NULL;

  return header;
}

size_t size(linked_list* l) {

  return l->size;
}

bool empty(linked_list* l) {

  if (l->next == NULL) {
    return true;
  } else {
    return false;
  }
}

error value_at(linked_list* l, size_t i, value* v) {
  if (i < 0 || i > l->size) {

    return INDEX_OUT_OF_BOUND;
  }
  linked_list *p = l->next;

  while(i--) {
    p = p->next;
  }

  *v = *p;

  return SUCCESS;
}


error push_front(linked_list* l, value v) {
  linked_list* node = (linked_list*) malloc(sizeof(linked_list));

  if (node == null) {
    return INSUFFICIENT_MEMORY;
  }

  linked_list* front = l->next;
  l->next = node;
  node->next = front;
  node->value = v;

  l->size += 1;

  return success;
}


error pop_front(linked_list* l, value* v) {
  if (l->next == NULL) {
    return NO_VALUE;
  }

  value result;
  linked_list* front = l->next;
  result = front->value;

  l->next = l->next->next;
  l->size -= 1;

  free(front);

  *v = result;
  return SUCCESS;
}

error push_back(linked_list* l, value v) {
  linked_list* pl = l;

  while(pl->next) {
    pl = pl->next;
  }

  linked_list* node = (linked_list*) malloc(sizeof(linked_list));

  if (node == NULL) {
    return INSUFFICIENT_MEMORY;
  }

  node->next = NULL;
  node->value = v;
  pl->next = node;

  l->size += 1;

  return SUCCESS;
}

error pop_back(linked_list* l, value* v) {
  linked_list* pl = l;
  linked_list* end_ptr, before_end_ptr;

  if (l->size == 0) {
    return NO_VALUE;
  }

  // 找到倒数第二个节点
  while(pl->next->next) {
    pl = pl->next;
  }

  before_end_ptr = pl;
  end_ptr = pl->next;

  *v = end_ptr->value;
  before_end_ptr->next = NULL;

  l->size -= 1;

  free(end_ptr);

  return SUCCESS;
}

error front(linked_list* l, value* v) {
  if (l->size == 0) {
    return NO_VALUE;
  }

  *v = l->next->value;

  return SUCCESS;
}

error back(linked_list* l, value* v) {
  if (l->size ==0) {
    return NO_VALUE;
  }

  linked_list* pl = l;

  while(pl->next) {
    pl = pl->next;
  }

  *v = pl->value;

  return SUCCESS;
}

error insert(linked_list* l, size_t i, value v) {
  if (i >= l->size) {
    return INDEX_OUT_OF_BOUND;
  }

  linked_list* node = (linked_list*) malloc(sizeof(linked_list));
  if (node == NULL) {
    return INSUFFICIENT_MEMORY;
  }

  node->value = v;

  linked_list* p = l;
  linked_list* tmp;
  size_t counter = i;

  while(counter--) {
    p = p->next;
  }

  tmp = p->next;
  p->next = node;
  node->next = tmp;

  l->size += 1;

  return SUCCESS;
}

error erase(linked_list* l, size_t i) {

  if (i >= l->size) {
    return INDEX_OUT_OF_BOUND;
  }

  linked_list* p = l;
  size_t counter = i;

  while(counter--) {
    p = p->next;
  }

  linked_list* ip = p->next;

  p->next = p->next->next;

  free(ip);

  l->size -= 1;

  return SUCCESS;
}

/*
  NULL    -- -> -- -> -- -> --
    p     c     n

  NULL <- --    -- -> -- -> --
          p     c     n
 */
void reverse(linked_list* l) {

  if (l->size <= 1) {
    return l;
  }

  linked_list* previous = NULL;
  linked_list* current = l->next;
  linked_list* nxt = current->next;

  while(nxt) {
    current->next = previous;
    previous = current;
    current = nxt;
    next = nxt->next;
  }

  l->next = current;
}

error value_n_from_end(linked_list* l, size_t n, value* v) {
  //TODO: implement;
  return SUCCESS;
}

int remove_value(value v) {
  //TODO: implement;
  return 0;
}
