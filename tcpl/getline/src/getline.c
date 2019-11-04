#include <stdio.h>
#include <string.h>

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


/*
  abcdef
  fedcba
 */
void reverse(char* str, int len) {
  for(int l = 0, r = len -1; l < r; l++, r--) {
    char tmp;
    tmp = str[l];
    str[l] = str[r];
    str[r] = tmp;
  }
}


int strindex(char* str, char* substr) {
  int i, j, k;
  for (i = 0; str[i] != '\0'; i++) {
    for(j = i, k = 0; substr[k] != '\0' && str[j] == str[k]; j++, k++){
    }

    if (k > 0 && substr[k] == '\0') {
      return i;
    }
  }
  return -1;
}
