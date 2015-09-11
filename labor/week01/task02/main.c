#include "strswap.h"
#include <stdio.h>

int main() {
  char s1[10] = "asd123aa";
  char s2[10] = "345ASD";
  printf("Before: %s %s\n", s1, s2);
  strswap2(s1, s2);
  printf("After: %s %s\n", s1, s2);
  
  return 0;
}
