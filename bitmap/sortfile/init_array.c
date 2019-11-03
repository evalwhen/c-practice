#include "initarray.h"
#include "memoryusage.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int data[10000000];

int main() {
  report_current_mem_usage(0);

  clock_t start, end;
  double cpu_time_used;

  init_ele(data, 100);

  report_current_mem_usage(1);

  // -----------------------------------------------------------
  start = clock();

  // 只初始化单个元素。(当前需要访问的元素)。
  init_ele(data, 101);
  // 一次性初始化所有元素;
  memset(data, 0, 10000000 * sizeof(int));

  end = clock();
  cpu_time_used = ((double)(end - start));
  printf("took %lf useconds to execute \n", cpu_time_used);
  // ----------------------------------------------------------


  if (init_check(data, 100) == HAS_INIT) {
    printf("%d nth element has been inited.\n", 100);
  }
}
