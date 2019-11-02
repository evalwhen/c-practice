#include "bitmap.h"
#include <string.h>

static int bitmap[1 + BITMAP_MAX_SIZE/BITSPERWORD];

/*   每一位(bit)表示一个整数在 bitmap 集合中是否出现,
     也就是说 bitmap 中的每个元素只能出现一次。

     如果需要表示 允许重复元素出现, 且重复次数有最高限制的集合,
     那么只用一位只能表示元素出现了一次或者零次，因此可以用多位来
     表示每个元素出现的次数。
*/

// i >> SHIFT == (floor i (expt 2 SHIFT))
// i & MASK == (rem i (expt 2 SHIFT))

void init_bitmap() { memset (bitmap, 0, sizeof (bitmap));}
void set(int i) { bitmap[i >> SHIFT] |= 1 << (i & MASK); };
void clr(int i) { bitmap[i >> SHIFT] &= ~(1 << (i & MASK)); };
int test(int i) { return bitmap[i >> SHIFT] & (1 << (i & MASK));};

