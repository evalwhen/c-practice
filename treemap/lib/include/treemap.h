#ifndef TREEMAP_LIB_H__
#define TREEMAP_LIB_H__

#include <stdbool.h>
#include <stdlib.h>
#include <inttypes.h>

typedef int KeyType;
typedef int ValueType;

typedef struct _Entry {
  KeyType key;
  ValueType value;
} Entry;

typedef struct _Node Node;

typedef enum _Color {Black = 0, Red = 1} Color;

struct _Node {
  Entry ele;
  Node *parent;
  Node *left;
  Node *right;
  int aux;  // 被 AVL 和 RedBlack rebalance 复用。
};

typedef struct _TreeMap* TreeMap;

struct _TreeMap {
  Node *root;
  size_t size;
};

size_t size(TreeMap t);
Node* root(TreeMap t);

TreeMap new_treemap();
void put(TreeMap t, KeyType key, ValueType value);
ValueType get(TreeMap t, KeyType key);
ValueType delete(TreeMap t, KeyType key);
Entry* values(TreeMap t);
void destruct_treemap(TreeMap t);

#endif
