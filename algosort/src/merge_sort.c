#include "algosort.h"
#include <stddef.h>
#include <stdio.h>

void merge_sort(int* seq, size_t sz) {

  if (sz < 2) {
    return;
  }

  int left_len = sz / 2;
  int right_len = sz - sz / 2;
  int left[left_len];
  int right[right_len];

  int k = 0;
  for (int i = 0; i < left_len; i++, k++) {
    left[i] = seq[k];
  }

  for (int j = 0; j < right_len; j++, k++) {
    right[j] = seq[k];
  }

  merge_sort(left, left_len);
  merge_sort(right, right_len);
  merge(left, right, seq, left_len, right_len);
}

void merge(int *left, int *right, int *dest, size_t left_len, size_t right_len) {

  int i, j;
  i = j =  0;

  while ((i + j) < (left_len + right_len)) {
    if (i == left_len) {
      dest[i+j] = right[j];
      j++;
    } else if (j == right_len) {
      dest[i+j] = left[i];
      i++;
    } else {
      if (left[i] > right[j]) {
        dest[i+j] = right[j];
        j++;
      } else {
        dest[i+j] = left[i];
        i++;
      }
    }
  }
}
