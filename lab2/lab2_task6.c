#include <stdio.h>
#include <stdlib.h>

int main()
{
    int **p;

    int x = 10;
    int y = 11;
    int z = 12;

    int *ptr = malloc(sizeof(int) * 3);
    *ptr = x;
    *(ptr + 1) = y;
    *(ptr + 2) = z;

    p = &ptr;

    free(ptr);
    // dont need free(p), only need to free address with allocated memory, which is at ptr
    // possibly works using *p
    return 0;
}