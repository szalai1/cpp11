#include <cstdio>

void hanoi(int n, char honnan, char seged, char hova, int *num) {
  if (n == 0) return;
  hanoi(n-1, honnan, hova, seged,num);
  printf("%d lepes rakj 1-et: %c->%c\n",  *num, honnan, hova);
  *num+=1;
  hanoi(n-1, seged, honnan, hova, num);
}

int main() {
  int num = 1;
  hanoi(4, 'A', 'B', 'C', &num);
  return 0;
}
