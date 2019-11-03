#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"
#include "fourbitmap.h"
#include "memoryusage.h"

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
  init_bitmap();
  int expect;
  int value = 9999;
  set(value);
  expect = 0 | (1 << (value & 0x1F));

  EXPECT_EQ_INT(expect, test(value));

  clr(value);
  EXPECT_EQ_INT(0, test(value));
}
/*
  max * fourbit
  1111 1111 1111 1111   1111 1111 1111 0010
  15    14   13   12    11   10    9    8
  7     6     5    4     3    2    1    0
  28    24   20   16    12    8    4    0
*/
static void test_fourbitmap_t() {
    int value = 8;
    int i = 0;
    int total = 15;
    for (; i < total; i++) {
        four_set(value);
    }
   int result = four_test(value);

    EXPECT_EQ_INT(total, result);
}
static void test_get_memory_kb() {
  // bug code. 3979 segmentation fault (core dumped)
  /* long* vmsize_kb; */
  /* long* vmrss_kb; */
  /* int res = get_memory_usage_kb(vmsize_kb, vmrss_kb); */
  init_fourbitmap();

  long vmsize_kb;
  long vmrss_kb;
  int res = get_memory_usage_kb(&vmsize_kb, &vmrss_kb);


  fprintf(stdout, "Current memory usage: VmRSS = %ld, VmSize = %ld\n", vmrss_kb, vmsize_kb);

  EXPECT_EQ_INT(res, 0);
}

static void test_size_of_array() {
  int shift[256];
  EXPECT_EQ_INT(1024, sizeof(shift));
}

static void run_all_test() {
  test_t();
  test_get_memory_kb();
  test_fourbitmap_t();
  test_size_of_array();
}




int main() {
  run_all_test();
  printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
  return main_ret;
}
