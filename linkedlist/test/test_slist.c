#include "slist.h"
#include <stdio.h>

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;
static int x = 0, y = 1, z = 2;

static bool is_equal(Value a, Value b) {
  int *x, *y;
  x = (int*) a;
  y = (int*) b;
  return (*x == *y) ? true : false;
}

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


static void test_push_back() {
  LinkList l;
  l = NULL;
  push_back(&l, (Value)(0));
  push_back(&l, (Value)(1));
  push_back(&l, (Value)(2));
  EXPECT_EQ_INT(3, size(l));
  EXPECT_EQ_INT((Value)(2), back(l));

  destruct(&l);
}

static void test_pop_back() {
  LinkList l;
  l = NULL;
  push_back(&l, (Value)(0));
  push_back(&l, (Value)(1));
  push_back(&l, (Value)(3));
  EXPECT_EQ_INT(3, size(l));
  Value v = pop_back(&l);
  EXPECT_EQ_INT(2, size(l));
  EXPECT_EQ_INT((Value)(3), v);
  EXPECT_EQ_INT((Value)(1), pop_back(&l));
  EXPECT_EQ_INT((Value)(0), pop_back(&l));
  EXPECT_EQ_INT((Value)(0), pop_back(&l));


  EXPECT_EQ_INT(0, size(l));


  destruct(&l);
}

static void test_back() {
  LinkList l;
  l = NULL;
  push_back(&l, (Value)(0));
  push_back(&l, (Value)(1));
  push_back(&l, (Value)(2));
  EXPECT_EQ_INT((Value) 2, back(l));

  destruct(&l);
}

static void test_insert() {
  LinkList l;
  l = NULL;
  insert(&l, 0, (Value) 0);
  insert(&l, 1, (Value) 1);
  insert(&l, 2, (Value) 2);
  EXPECT_EQ_INT(3, size(l));

  EXPECT_EQ_INT((Value) 0, value_at(l, 0));
  EXPECT_EQ_INT((Value) 1, value_at(l, 1));
  EXPECT_EQ_INT((Value) 2, value_at(l, 2));

  destruct(&l);
}

static void test_erase() {
  LinkList l;
  l = NULL;
  insert(&l, 0, (Value) 0);
  insert(&l, 1, (Value) 1);
  insert(&l, 2, (Value) 2);
  EXPECT_EQ_INT(3, size(l));

  EXPECT_EQ_INT((Value) 0, erase(&l, 0));
  EXPECT_EQ_INT((Value) 1, front(l));

  EXPECT_EQ_INT(2, size(l));

  destruct(&l);
}

static void test_remove_value() {
  LinkList l;
  l = NULL;
  push_back(&l, (Value) &x);
  push_back(&l, (Value) &y);
  push_back(&l, (Value) &z);
  push_back(&l, (Value) &x);
  push_back(&l, (Value) &z);
  EXPECT_EQ_INT(5, size(l));

  EXPECT_EQ_INT(2, remove_value(&l, (Value) &z, is_equal));

  EXPECT_EQ_INT(3, size(l));
  EXPECT_EQ_INT((Value) &x, back(l));

  destruct(&l);
}

static void run_all_test() {
  test_push_back();
  test_pop_back();
  test_back();
  test_insert();
  test_erase();
  test_remove_value();
}

int main() {

  run_all_test();

  printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
  return 0;
}
