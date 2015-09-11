#include "strswap.h"

void strswap(char *s1, char *s2) {
  int len_s1 = strlen(s1);
  char *tmp_str = (char *) malloc(sizeof(char) * (1 +len_s1));
  strcpy(tmp_str, s1);
  strcpy(s1, s2);
  strcpy(s2, tmp_str);
  free(tmp_str);
  
}

void strswap2(char *s1, char *s2) {
  char tmp;
  int end_sign=0;
  int ii = 0;
  while( end_sign != 2) {
    tmp = s1[ii];
    s1[ii] = s2[ii];
    s2[ii] = tmp;
    if (s1[ii] == '\0') {
      end_sign+=1;
    }
    if (s2[ii] == '\0') {
      end_sign+=1;
    }
    ii+=1;
  }
}
