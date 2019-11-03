#include <string.h>

int _gcd(int i, int j);

int rotate_str(char* str, int i) {

  int len = strlen(str);

  if (i <= 0 || i >= len) {
    return -1;
  }

  int total = _gcd(strlen(str), i);

  for (int j = 0; j < total; j++) {
    int k = j;
    int t = str[k];
    while(1) {
      int l = k + i;

      if (l >= len) {
        l = l - len;
      }

      if (l == j) {
        break;
      }
      str[k] = str[l];
      k = l;
    }
    str[k] = t;
  }

  return 0;
}

int _gcd(int i, int j){
  while (i != j) {
    if (i > j) {
      i -= j;
    } else {
      j -= i;
    }
  }

  return i;
}
