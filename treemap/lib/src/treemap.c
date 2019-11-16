#include "treemap.h"
#include <assert.h>
#include <string.h>

static Node* tree_search(Node* n, KeyType key);
static Node* tree_search(Node* n, KeyType key);
static bool is_external(Node* n);
static bool is_internal(Node* n);
static Node* create_node(Color color);
static Node* tree_max(Node* n);
static size_t num_children(Node* n);
static Node* sibling(Node* n);
static bool is_root(Node* n);
static void free_node(Node* n);

size_t size(TreeMap t) {
  return t->size;
}

Node* root(TreeMap t) {
  return t->root;
}

TreeMap new_treemap() {
  Node* root = create_node(Black);
  TreeMap t;

  t = (TreeMap) malloc(sizeof(struct _TreeMap));
  t->root = root;
  t->size = 0;

  return t;
}

void put(TreeMap t, KeyType key, ValueType value) {
  Node* position = tree_search(t->root, key);

  if (position->ele.key == key) {

    position->ele.value = value;

  } else {

    position->ele.key = key;
    position->ele.value = value;
    position->color = Red;
    Node *left, *right;
    left = create_node(Black);
    right = create_node(Black);

    position->left = left;
    position->right = right;

    left->parent = position;
    right->parent = position;
    t->size += 1;
  }
}

ValueType get(TreeMap t, KeyType key) {
  Node* position = tree_search(t->root, key);

  if (is_external(position)) {
    // todo: define null value;
    return 0;
  } else {

    return position->ele.value;
  }
}

ValueType delete(TreeMap t, KeyType key) {
  Node* position = tree_search(t->root, key);
  ValueType result;

  // todo: define null value;
  result = 0;

  if (is_external(position)) {
    return result;

  } else {
    result = position->ele.value;
    if (is_internal(position->left) && is_internal(position->right)) {
      Node* replacement = tree_max(position->left);
      replacement->ele.value = position->ele.value;
      position = replacement;
    }
    Node *leaf, *child;

    child = is_internal(position->left) ? position->left : position->right;
    leaf = sibling(child);

    child->parent = position->parent;
    if (is_root(position)) {
      t->root = child;
    } else {

      // position is left node
      if (position->parent->left == position) {
        position->parent->left = child;
      } else {
        position->parent->right = child;
      }
    }

    free(leaf);
    free(position);

    t->size -= 1;
  }

  return result;
}

Entry* values(TreeMap t);

void destruct_treemap(TreeMap t) {
  if (t == NULL) {
    return;
  } else {
    free_node(t->root);
    free(t);
  }
}

static Node* tree_search(Node* n, KeyType key) {
  if (is_external(n)) {
    return n;
  } else {
    if (n->ele.key < key) {

      return tree_search(n->right, key);
    } else if (n->ele.key > key) {

      return tree_search(n->left, key);
    } else {

      return n;
    }
  }
}

static bool is_external(Node* n) {
  return (n->left == NULL && n->right == NULL);
}

static bool is_internal(Node* n) {
  return (n->left != NULL && n->right != NULL);
}

static Node* create_node(Color color) {
  Node* root;
  root = (Node* ) malloc(sizeof(Node));

  root->ele.key = ~0;
  root->ele.value = ~0;
  root->parent = NULL;
  root->left = NULL;
  root->right = NULL;
  root->color = color;

  return root;
}


static Node* tree_max(Node* n) {
  if (is_external(n)) {
    return n->parent;
  } else {
    tree_max(n->right);
  }
}


static size_t num_children(Node* n) {
  size_t counter = 0;

  if (n->left != NULL) counter++;
  if (n->right != NULL) counter++;

  return counter;
}


static Node* sibling(Node* n) {
  // n is root
  if (n->parent == NULL) {
    return NULL;
  } else {
    // n is left
    if(n->parent->left == n) {
      return n->parent->right;
    } else {
      return n->parent->left;
    }
  }
}

static bool is_root(Node* n) {
  return n->parent == NULL;
}


static void free_node(Node* n) {

  if (n == NULL) {
    return;
  } else {
    free_node(n->left);
    free_node(n->right);
    free(n);
  }
}
