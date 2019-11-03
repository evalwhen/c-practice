#include <stddef.h>
#include <stdlib.h>
#include "initarray.h"

/*   from 数组下标 i 对应的元素值v，对应了 to 中记录的 data 初始化下标;
   如果 to[v] = i && v < top; 那么 dota[i] 已经被初始化过了。

     这里的 from 感觉好像是多余的, 因为 to 数组和 top 已经记录了所有的已经
   被初始化的所有 data 下标。但只用 to 和 top 不能方便的查看某个元素是否已经
   被初始化过了。

     也可以这样想: from 和 data 数组长度相同，一旦 data 中某个位置(i)被初始化，
   那么就对 from 中相同位置签名(from[i] = top++), top 从零开始。但是只用 from 一个数
   组无法保证签名是用户自己签名还是被随机内存值签名。因此需要第二个数组 to, 用
   来保存所有已经被初始化了的位置 to[top] = i。要验证位置 i 是否已经被初始化过，
   只需要验证 to[from[i]] == i。可以说是非常巧妙。
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
