#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *p = malloc(sizeof(int));
    int *q = malloc(sizeof(int) * 2);

    *p = 1;
    *q = 10;

    printf("p: %p\t q: %p\n", p, q);

    q = p;

    printf("p: %p\t q: %p", p, q);

    free(q);
    free(p);
    // q points to same address as p after q = p
    // old addresss of q no longer has a pointer, no way to free stuff at that address
    return 0;
}