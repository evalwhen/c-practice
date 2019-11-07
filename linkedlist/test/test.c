#include "list.h"
#include <stdio.h>

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

static void print_linked_list(linked_list* l);

#define EXPECT_EQ_BASE(equality, expect, actual, format)\
  do {\
    test_count++;\
    if (equality)\
      test_pass++;\
    else {\
      fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual); \
      main_ret = 1;\
    }\
  } while(0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")

static void test_new_list() {
  linked_list* l = new_linked_list();
  value x;
  EXPECT_EQ_INT(true, empty(l));
  /* EXPECT_EQ_INT(INDEX_OUT_OF_BOUND, value_at(l, 0, &x)); */
  destruct(l);
}

static void test_push_front_and_reverse() {
  linked_list* l = new_linked_list();
  int x = 0, y = 1, z = 3;
  push_front(l, &x);
  push_front(l, &y);
  push_front(l, &z);

  EXPECT_EQ_INT(3, size(l));
  EXPECT_EQ_INT(3, *((int*)front(l)));

  print_linked_list(l);
  reverse(l);
  print_linked_list(l);
  push_back(l, &z);

  EXPECT_EQ_INT(4, size(l));
  print_linked_list(l);
  destruct(l);

}

static void print_linked_list(linked_list* l) {
  linked_list* p = l->next;
  while(p) {
    printf("%d ", *(int*)p->value);
    p = p->next;
  }
  printf("\n");
}

static void run_all_test() {
  test_new_list();
  test_push_front_and_reverse();
}

int main() {

  run_all_test();

  printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
  return 0;
}
