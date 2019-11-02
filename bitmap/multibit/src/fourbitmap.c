#include "fourbitmap.h"

int fourbitmap[1 + FBITMAP_MAX_SIZE * FOURBIT / FBITSPERWORD];

// i >> SHIFT == (floor i (expt 2 SHIFT))
// i & MASK == (rem i (expt 2 SHIFT))

/*
  max * fourbit
  1111 1111 1111 1111   1111 1111 1111 0010
   15    14   13   12    11   10    9    8
   7     6     5    4     3    2    1    0
   28    24   20   16    12    8    4    0

   0111
   1000 &
   1111
   1000
*/
void four_set(int i) {
    int pos = ((i & FMASK) << 2);
    int x = fourbitmap[i >> FSHIFT];
    int mask = x & (FOUR_BIT_MASK << pos);
    int fourbit = mask >> pos;
    int tmp = (fourbit + 1) & FOUR_BIT_MASK;
    x = x & ~ (FOUR_BIT_MASK << pos);
    x = x | (tmp << pos);

    fourbitmap[i >> FSHIFT] = x;
};

void four_clr(int i) {
  int x = fourbitmap[i >> FSHIFT];
  int mask = x & (1111 << ((i & FMASK) << 2));
  int fourbit = mask >> ((i & FMASK) << 2);
  int tmp = (fourbit - 1) & 1111;
  x = x & ~(1111 << ((i & FMASK) << 2));
  x = x | (tmp << ((i & FMASK) << 2));

  fourbitmap[i >> FSHIFT] = x;
};
int four_test(int i) {
  int x = fourbitmap[i >> FSHIFT];
  int mask = x & (FOUR_BIT_MASK << ((i & FMASK) << 2));
  int fourbit = mask >> ((i & FMASK) << 2);

  return fourbit;
};
