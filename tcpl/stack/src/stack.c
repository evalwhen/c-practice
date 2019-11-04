#include "stack.h"
#include <stdio.h>

static double stack[MAX_N];
static int top = 0;

int push(double d) {
  if (top >= MAX_N) {
    return -1;
  } else {
    stack[top++] = d;
      return  0;
  }
}

double pop(void) {
  if (top == 0) {
    return 0.0;
  } else {
    return stack[--top];
  }
}
