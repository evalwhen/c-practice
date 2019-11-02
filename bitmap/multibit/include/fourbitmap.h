#ifndef FOURBITMAP_H__
#define FOURBITMAP_H__

#define FBITSPERWORD  32
#define FSHIFT  3
#define FOURBIT 4
#define FMASK  0x7
#define FBITMAP_MAX_SIZE  10000000
#define FOUR_BIT_MASK 0xF

void init_fourbitmap();
void four_set(int i); // add element
void four_clr(int i); // remove element
int four_test(int i); // check that the element exists

#endif
