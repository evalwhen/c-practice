#include "vector.h"
#include <stdio.h>

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

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


static void test_insert() {

  vector* v = new_vector();
  int ret = insert(v, 0, 1000);
  EXPECT_EQ_INT(1000, at(v, 0));
  EXPECT_EQ_INT(1, size(v));
  EXPECT_EQ_INT(INITIAL_CAPACITY, capacity(v));

  insert(v, 0, 1001);

  EXPECT_EQ_INT(1001, at(v, 0));
  EXPECT_EQ_INT(2, size(v));
  EXPECT_EQ_INT(INITIAL_CAPACITY, capacity(v));

  destruct(v);
}

static void test_push() {
  vector* v = new_vector();
  for (int i = 0; i < 9; i++){
    push(v, i);
  }
  EXPECT_EQ_INT(9, size(v));
  EXPECT_EQ_INT(18, capacity(v));
  EXPECT_EQ_INT(8, at(v, 8));
  EXPECT_EQ_INT(INDEX_OUT_OF_BOUND, at(v, 9));

  destruct(v);
}

static void test_prepend() {
  vector* v = new_vector();
  prepend(v, 10);
  EXPECT_EQ_INT(10, at(v, 0));

  prepend(v, 11);
  EXPECT_EQ_INT(11, at(v, 0));


  destruct(v);
}

static void test_pop() {
  vector* v = new_vector();
  for (int i = 0; i < 9; i++){
    push(v, i);
  }
  EXPECT_EQ_INT(9, size(v));
  EXPECT_EQ_INT(18, capacity(v));

  EXPECT_EQ_INT(8, pop(v));
  EXPECT_EQ_INT(8, size(v));
  EXPECT_EQ_INT(18, capacity(v));

  for (int i = 0; i < 4; i++) {
    pop(v);
  }
  EXPECT_EQ_INT(4, size(v));
  EXPECT_EQ_INT(9, capacity(v));


  destruct(v);
}

static void test_delete() {
  vector* v = new_vector();
  for (int i = 0; i < 9; i++){
    push(v, i);
  }

  EXPECT_EQ_INT(6, delete(v, 6));
  EXPECT_EQ_INT(8, size(v));

  destruct(v);
}

static void test_find() {
  vector* v = new_vector();
  for (int i = 0; i < 9; i++){
    push(v, i);
  }

  EXPECT_EQ_INT(6, find(v, 6));
  EXPECT_EQ_INT(-1, find(v, 100));

  destruct(v);
}

static void run_all_test() {
  test_insert();
  test_push();
  test_prepend();
  test_pop();
  test_delete();
  test_find();
}

int main() {

  run_all_test();

  printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
  return 0;
}
