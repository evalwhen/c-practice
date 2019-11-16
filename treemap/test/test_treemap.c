#include "treemap.h"
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

static void test_treemap() {
  TreeMap t;

  t = new_treemap();
  put(t, 2, 3);
  put(t, 3, 4);
  put(t, 5, 6);


  EXPECT_EQ_INT(3, get(t, 2));
  EXPECT_EQ_INT(4, get(t, 3));
  EXPECT_EQ_INT(6, get(t, 5));

  delete(t, 2);

  EXPECT_EQ_INT(0, get(t, 2));
  EXPECT_EQ_INT(2, size(t));

  destruct_treemap(t);
}

static void run_all_test() {
  test_treemap();
}

int main() {

  run_all_test();

  printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
  return 0;
}
