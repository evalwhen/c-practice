#ifndef BITMAP_H__
#define BITMAP_H__

#define BITSPERWORD  32
#define SHIFT  5
#define MASK  0x1F
#define N  100

void set(int i); // add element
void clr(int i); // remove element
int test(int i); // check that the element exists

#endif
