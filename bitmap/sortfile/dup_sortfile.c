/* 场景：文件f，由大小不能超过7位的整数组成，每个整数用换行符分隔
   每个数字可重复，但不能超过10次。

   将整数从大到小排序，并将结果写入新的文件,

   可以使用 bitmap 数据结构的扩展版本 multibitmap,
   bitmap 表示的集合元素不能重复，但 multibitmap 表示的集合
   元素可以重复，但有重复次数限制，即用多个bit来表示某个整数。
   具体实现见 multibit library。
 */

#include "fourbitmap.h"
#include <stdio.h>
#include <inttypes.h>

int main() {
  FILE* f = fopen("rand_no_dup_int.txt", "r+");
  FILE* f2 = fopen("sort_rand_no_dup_int.txt", "w");

  char* line = NULL;
  size_t len = 0;

  while(getline(&line, &len, f) != -1) {
    //TODO: 错误处理。
    int value = strtoimax(line, NULL, 10);
    four_set(value);
  }

  int i;
  for (i = 0; i < FBITMAP_MAX_SIZE; i++) {
    int total = four_test(i);
    if (total != 0) {
      int j;
      for (j = 0; j < total; j++) {
        fprintf(f2, "%d\n", i);
      }
    }
  }

  return 0;
}
