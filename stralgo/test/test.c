#include "rotatestr.h"
#include <stdio.h>
#include <string.h>

int main() {

  // 错误写法，将会存储"abcdefghijkl" .rodata 段上，不可写，segmentation fault
  // char* str = "abcdefghijkl";
  char str[] = "abcdefghijkl";

  rotate_str(str, 3);

  printf("%s\n", str);
}
