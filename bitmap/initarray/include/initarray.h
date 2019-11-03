#ifndef BITMAP_INITARRAY_H__
#define BITMAP_INITARRAY_H__

/* Problem 1.9
    在实践中，经常会使用空间换时间的做法。比如 bitmap,
  当 bitmap 所能表示的集合越大，使用它来排序时所需要的
  时间就越少（见 n_pass_sort.c)。

    但是, 当数组越大，初始化它反而需要更多的时间。
  这里通过一种方法，只在第一次访问某个元素时才初始化它。

    这种方法也是通过空间换时间的做法来抵消大数组的初始化时间,
  适用的场景: 内存空间很多，时间敏感，数组访问较随机。

    其中额外的空间被用来记录已经被初始化过的元素下标。
 */

enum State {NO_INIT, HAS_INIT};

// 初始化data[i] = 0
int init_ele(int *data, int i);
// 检查 data[i] 是否已经被初始化过
enum State init_check(int *data, int i);

#endif
