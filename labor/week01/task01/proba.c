#include <stdio.h>
 
void bomb(int i) {
    if (i == 0) {
        int *p = NULL;
        *p = 1234;
    } else {
        printf("Ticking %d...\n", i);
    }
}
 
int main(void) {
    for (int i = 6; i > 0; --i)
        bomb(i-1);
    printf("Boom!\n");
}
