#include "algosort.h"
#include <stddef.h>

void swap(int *a, int *b);
int partition(int *seq, int low, int high);

void quick_sort(int *seq, int low, int high) {

  if (low < high) {

    int p = partition(seq, low, high);
    quick_sort(seq, low, p - 1);
    quick_sort(seq, p + 1, high);
  }
}

void swap(int* a, int* b) {
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

int partition(int* seq, int low, int high) {
  int pivot = seq[high];
  int i = low - 1;

  for (int j = low; j < high; j++) {

    if (seq[j] < pivot) {
      i++;
      swap(seq + i, seq + j);
    }
  }

  swap(seq + i + 1, seq + high);

  return i + 1;
}
