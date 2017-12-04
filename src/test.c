//DO NOT SUBMIT THIS FILE

#include <stdio.h>
#include <stdlib.h>
typedef struct {int x; int* ptr;}* ms;
int main(void) {
//    long n = 3;
//    printf("%lld\n", n);
//    ms i = malloc(sizeof(ms));
//    i->x = 10;
//    n = i;
//    printf("%p, %p\n", n, i);
//    printf("%d\n", i->x);
//    free(n);
////    free(i);
//    printf("%p, %p\n", n, i);
//    printf("%d\n", i->x);
    // Conclusion, grid[x] = &struct is OK.
    printf("%d\n", sizeof(short));
    printf("%d\n", sizeof(int));
    return 0;
}