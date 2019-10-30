#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"
#include "memory.h"

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        test_count++;\
        if (equality)\
            test_pass++;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
            main_ret = 1;\
        }\
    } while(0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")

static void test_t() {
  int expect;
  int value = 9999;
  set(value);
  expect = 0 | (1 << (value & 0x1F));

  EXPECT_EQ_INT(expect, test(value));

  clr(value);
  EXPECT_EQ_INT(0, test(value));
}

static void test_get_memory_kb() {
  // bug code. 3979 segmentation fault (core dumped)
  /* long* vmsize_kb; */
  /* long* vmrss_kb; */
  /* int res = get_memory_usage_kb(vmsize_kb, vmrss_kb); */

  long vmsize_kb;
  long vmrss_kb;
  int res = get_memory_usage_kb(&vmsize_kb, &vmrss_kb);


  fprintf(stdout, "Current memory usage: VmRSS = %ld, VmSize = %ld\n", vmrss_kb, vmsize_kb);

  EXPECT_EQ_INT(res, 0);
}

static void run_all_test() {
  test_t();
  test_get_memory_kb();
}


int main() {
  run_all_test();
  printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
  return main_ret;
}
