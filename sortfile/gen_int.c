#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10000000
#define M 1000

uint32_t *x;

uint32_t randint (uint32_t a, uint32_t b)
{
  uint32_t range;
  uint32_t r, max;

  /*
   * We want a number in the range a..b.
   */
  range = b - a + 1;

  /*
   * Discard top random numbers for uniform distribution in this range, by
   * removing the remainder.
   */
  max = RAND_MAX;
  if (range < RAND_MAX) {
    max -= (RAND_MAX % range);
  }

  do {
    r = rand();
  } while (r >= max);


  // if (RAND_MAX * RAND_MAX < INT_MAX)

  //    if (b > RAND_MAX) {
  //	r += RAND_MAX * rand();
  //    }

  r %= range;

  return (a + r);
}

int main() {

  x = malloc(N * sizeof(*x));

  uint32_t i;
  for (i = 0; i < N; i++) {
    x[i] = i;
  }

  srand(0);


  FILE* f = fopen("rand_no_dup_int.txt", "w");
  for (i = 0; i < M; i++) {
    uint32_t g = randint(i, N-1);
    uint32_t tmp;


    tmp = x[i];
    x[i] = x[g];
    x[g] = tmp;

    fprintf(f, "%d\n", x[i]);
  }

  fclose(f);
  free(x);

  return 0;
}
