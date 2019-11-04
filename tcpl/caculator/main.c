#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "getop.h"

#define NUMBER '0'
#define MAXOP 100

int main() {
  int type;
  double tmp;
  char s[MAXOP];
  while((type = getop(s)) != EOF) {
    switch(type) {
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '-':
      tmp = pop();
      push(pop() - tmp);
      break;
    case '*':
      push(pop() * pop());
      break;
    case '/':
      tmp = pop();
      if (tmp != 0.0) {
        push(pop() / tmp);
      } else {
        printf("error: 除零\n");
      }
      break;
    case '\n':
      printf("result: %g\n", pop());
      break;
    default:
      printf("无效的运算指令%s\n", s);
      break;
    }
  }
}
