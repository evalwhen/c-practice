#include "hashmap.h"
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

static void test_hashmap() {
  HashMap h;

  h = new_hashmap();

  int j = 10;
  for (int i = 0; i < 10; i++, j++) {
    add(h, i, j);
    EXPECT_EQ_INT(j, get(h, i));
  }

  EXPECT_EQ_INT(10, entry_size(h));

  EXPECT_EQ_INT(true, exists(h, 8));

  remove_key(h, 8);

  EXPECT_EQ_INT(9, entry_size(h));
  EXPECT_EQ_INT(false, exists(h, 8));

  destruct_hashmap(h);
}

static void run_all_test() {
  test_hashmap();
}

int main() {

  run_all_test();

  printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
  return 0;
}
