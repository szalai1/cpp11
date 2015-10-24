#include <cstdio>

int num = 1;

void hanoi(int n, char honnan, char seged, char hova) {
    if (n == 0) return;
    hanoi(n-1, honnan, hova, seged);
    printf("%d lepes rakj 1-et: %c->%c\n", num, honnan, hova);
    num += 1;
    hanoi(n-1, seged, honnan, hova);
}
 
int main() {
    hanoi(4, 'A', 'B', 'C');
    return 0;
}
