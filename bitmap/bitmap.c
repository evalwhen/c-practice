#include "bitmap.h"

static int bitmap[1 + N/BITSPERWORD];

// i >> SHIFT == (floor i (expt 2 SHIFT))
// i & MASK == (rem i (expt 2 SHIFT))
void set(int i) { bitmap[i >> SHIFT] |= 1 << (i & MASK); };
void clr(int i) { bitmap[i >> SHIFT] &= ~(1 << (i & MASK)); };
int test(int i) { return bitmap[i >> SHIFT] & (1 << (i & MASK));};

