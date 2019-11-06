#include "vector.h"
#include <stdio.h>

int main() {
  vector v = new_vector();
  printf("vector size: %d\n", size(&v));
  printf("vector capacity: %d\n", capacity(&v));
}
