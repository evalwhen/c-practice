#include "getop.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// (1.1 - 22) * (5 + 4)
// 1.1 22 - 5 4 + *
// 1 2 -
int getop(char* s) {
  int i, c;
  int counter = 0;
  while ((s[0] = c = getc(stdin)) == ' ' || c == '\t'){
      counter = counter + 1;
      printf("counter: %d\n", counter);
  }

  s[1] = '\0';
  if (!isdigit(c) && c != '.') {
    return c;
  }
  i = 0;
  if (isdigit(c)) {
    while(isdigit(c = getc(stdin))) {
      s[++i] = c;
    }
  }

  if (c == '.') {
    s[++i] = c;
    while(isdigit(c = getc(stdin))) {
      s[++i] = c;
    }
  }
  if (c != EOF) {
    ungetc(c, stdin);
  }
  s[++i] = '\0';
  return NUMBER;
}
