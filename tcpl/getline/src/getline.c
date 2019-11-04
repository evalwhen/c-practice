#include <stdio.h>

int getline1(char* line, int maxlen) {

  int i, c;
  i = 0;
  while(i < maxlen &&(c = getchar()) != EOF) {
    if (c != '\n') {
      line[i] = c;
      i++;
    } else {
      break;
    }
  }
  line[i] = '\0';

  return i;
}

void copy(char* from, char* to) {

  int i;
  i = 0;
  while((to[i] = from[i]) != '\0'){
    i++;
  };
}
