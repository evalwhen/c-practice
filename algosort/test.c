#include "algosort.h"
#include <stdio.h>

#define N 6
int main(int argc, char* argv[]) {
  int seq[] = {1, 5, 4, 2, 3, 6};
  merge_sort(seq, N);

  for(int i = 0; i < N; i++) {
    printf("%d\n", seq[i]);
  }
  printf("\n");

  int seq2[] = {1, 5, 4, 2, 3, 6};

  quick_sort(seq2, 0, N-1);

  for (int i = 0; i < N; i++) {
    printf("%d\n", seq2[i]);
  }

  printf("\n");

  return 0;
}
