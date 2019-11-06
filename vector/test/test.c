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



int main() {
  vector v = construct();
  for (int i = 0; i < 9; i++){
    push(&v, i);
  }
  EXPECT_EQ_INT(9, size(&v));
  EXPECT_EQ_INT(18, capacity(&v));
  EXPECT_EQ_INT(1, at(&v, 1));
  EXPECT_EQ_INT(8, at(&v, 8));
  EXPECT_EQ_INT(INDEX_OUT_OF_BOUND, at(&v, 9));


  printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);

  destruct(&v);

  return 0;
}
