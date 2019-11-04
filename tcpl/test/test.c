#include "getline.h"
#include <stdio.h>
#include <string.h>


int main() {
  char line[MAX_N];
  char max_line[MAX_N];

  int len, max_len;

  max_len = 0;
  len = 0;
  while((len = getline1(line, MAX_N)) != 0) {
    if (len > max_len) {
      max_len = len;
      copy(line, max_line);
    }
  }

  printf("max_len: %d\n; line: %s\n", max_len, max_line);
}
