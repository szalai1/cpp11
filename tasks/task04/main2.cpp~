#include <cstdio>

int pow(int ex) {
  int val = 1;
  for (int i = 0; i < ex; ++i) {
    val=val* 2;
  }
  return val;
}

void hanoi(int n, char honnan, char seged, char hova, int bias) {
if (n == 0) return;
hanoi(n-1, honnan, hova, seged,bias);
printf("%d lepes rakj 1-et: %c->%c\n", bias + pow(n-1), honnan, hova);
hanoi(n-1, seged, honnan, hova, bias + pow(n-1));
}

int main() {
hanoi(4, 'A', 'B', 'C', 0);
return 0;
}
