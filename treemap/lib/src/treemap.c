#include "treemap.h"
#include <assert.h>
#include <string.h>

static Node* tree_search(Node* n, KeyType key);
static bool is_external(Node* n);
static bool is_internal(Node* n);
static Node* create_node();
static Node* tree_max(Node* n);
static size_t num_children(Node* n);
static Node* sibling(Node* n);
static bool is_root(Node* n);
static void free_node(Node* n);
static void rotate(TreeMap t, Node* n);
static Node* restructure(TreeMap t, Node* n);
static void rebalance_insert(TreeMap t, Node* n);
static void resolve_red(TreeMap, Node*);
static void rebalance_delete(TreeMap, Node*);
static void remedy_double_black(TreeMap, Node*);
static void rebalance(TreeMap, Node*);  // AVL
static int height(Node* p);
static void recompute_height(Node* p);
static bool is_balanced(Node* p);

size_t size(TreeMap t) {
  return t->size;
}

Node* root(TreeMap t) {
  return t->root;
}

TreeMap new_treemap() {
  Node* root = create_node();
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
    Node *left, *right;
    left = create_node();
    right = create_node();

    position->left = left;
    position->right = right;

    left->parent = position;
    right->parent = position;
    t->size += 1;

    rebalance_insert(t, position);
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

    if (is_internal(position->left)) {
        child = position->left;
    } else {
        child = position->right;
    }

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

    rebalance_delete(t, child);
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

static Node* create_node() {
  Node* root;
  root = (Node* ) malloc(sizeof(Node));

  root->ele.key = ~0;
  root->ele.value = ~0;
  root->parent = NULL;
  root->left = NULL;
  root->right = NULL;
  root->aux = Black;

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

static void rotate(TreeMap t, Node* n) {
  Node *x, *y, *z;
  x = n;
  y = x->parent;
  z = y->parent;

  if (y->left == x) {
    y->left = x->right;
    y->right->parent  = x;
    x->right = y;
  } else {
    y->right = x->left;
    x->left->parent = y;
    x->left = y;
  }

  x->parent = z;
  y->parent = x;

  if (z == NULL) {
    t->root = x;
  } else {
    if (y == z->left) {
      z->left = x;
    } else {
      z->right = x;
    }
  }
}

static Node* restructure(TreeMap t, Node* n) {
  Node *x, *y, *z;
  x = n;
  y = x->parent;
  z = y->parent;

  if ((x == y->right) == (y == z->right)) {
    rotate(t, y);
    return y; // 返回新的字树根节点
  } else {
    rotate(t, x);
    rotate(t, x);
    return x; // 返回新的字树根节点
  }
}


static void rebalance_insert(TreeMap t, Node* n) {
  // 新插入的节点不是root节点
  if (n->parent != NULL){
    n->aux = Red;
    resolve_red(t, n);
  }
}


static void resolve_red(TreeMap t, Node* n) {

  Node *middle, *uncle, *parent, *grand;
  parent = n->parent;

  // 打破红黑树的 red-propertity: 红节点的孩子节点都是黑节点
  if (parent->aux == Red) {
    uncle = sibling(parent);
    if (uncle->aux == Black) {
      middle = restructure(t, n);
      middle->aux = Black;
      middle->left->aux = Red;
      middle->right->aux = Red;
      // 相当于2-3-4树的split操作
    } else {
      grand = parent->parent;
      parent->aux = Black;
      uncle->aux = Black;

      // root-propertity: 根节点必须是黑节点
      if (!is_root(grand)) {
        grand->aux = Red;
        resolve_red(t, grand);
      }
    }
  }
}


static void rebalance_delete(TreeMap t, Node* p) {
  if (p->aux == Red) {
    p->aux = Black;
  } else {
    if (!is_root(p)) {
      Node* y = sibling(p);
      if (is_internal(y)) {
        if (y->aux == Black || is_internal(y->left)) {
          remedy_double_black(t, p);
        }
      }
    }
  }
}

static void remedy_double_black(TreeMap t, Node* p) {
  Node* y = sibling(p);
  Node* z = y->parent;

  if (y->aux == Black) {
    // 2-3-4 transfer
    if (y->left->aux == Red || y->right->aux == Red) {
      Node* red_child = (y->left->aux == Red) ? y->left : y->right;
      Node* middle = restructure(t, red_child);
      middle->aux = z->aux;
      middle->left->aux = Black;
      middle->right->aux = Black;
      // 2-3-4 fuse
    } else {
      y->aux = Red;
      if (z->aux == Red) {
          z->aux == Black;
      } else {
        if (!is_root(z)) {
          remedy_double_black(t, z);
        }
      }
    }
  } else {
    Node* z = y->parent;
    rotate(t, y);
    y->aux = Black;
    z->aux = Red;
    remedy_double_black(t, p);
  }
}

static int height(Node* p) {
  return p->aux;
}

static Node* taller_child(Node* p) {
  if (height(p->left) > height(p->right)) {
    return p->left;
  } else if (height(p->left) < height(p->right)) {
    return p->right;
  } else {
    if (p == p->parent->left) {
      return p->left;
    } else {
      return p->right;
    }
  }
}


static void recompute_height(Node* p) {
  int max = 0;
  if (height(p->left) >= height(p->right)) {
    p->aux = height(p->left) + 1;
  } else {
    p->aux = height(p->right) + 1;
  }
}

static bool is_balanced(Node* p) {
  int x = height(p->left) - height(p->right);
  if (x < 0) {
    x = -x;
  }

  return x <= 1;
}

static void rebalance(TreeMap t, Node* p) {
  int old_height, new_height;

  do {
    old_height = height(p);
    if (!is_balanced(p)) {
      Node* middle = restructure(t, taller_child(taller_child(p)));
      recompute_height(middle->left);
      recompute_height(middle->right);
      p = middle;
    }
    recompute_height(p);
    new_height = height(p);
    p = p->parent;
  } while(new_height != old_height && p != NULL);
}
