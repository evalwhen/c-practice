#include <stddef.h>
#include <stdlib.h>
#include "initarray.h"

/*   from 数组下标 i 对应的元素值v，对应了 to 中记录的 data 初始化下标;
   如果 to[v] = i && v < top; 那么 dota[i] 已经被初始化过了。

     这里的 from 感觉好像是多余的, 因为 to 数组和 top 已经记录了所有的已经
   被初始化的所有 data 下标。但只用 to 和 top 不能方便的查看某个元素是否已经
   被初始化过了。
*/
int* from = NULL;
// to 数组记录了已经被初始化了的 data 下标;
int* to = NULL;
int top = 0;

int init_ele(int* data, int i) {
  if (from == NULL) {
    from = (int*) malloc(sizeof(data));
  }

  if (to == NULL) {
    to = (int*) malloc(sizeof(data));
  }

  if (init_check(data, i) == NO_INIT) {
    to[top] = i;
    from[i] = top;
    // 默认初始化为 0
    data[i] = 0;
    top++;
  }

  return 0;
}

enum State init_check(int *data, int i) {
  if (to[from[i]] == i && from[i] < top) {
    return HAS_INIT;
  }

  return NO_INIT;
}
