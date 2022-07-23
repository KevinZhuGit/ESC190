#include <stdio.h>

int main()
{
    int x = 0;
    int *ptr = &x;
    printf("x contains the value %d at location %p\n", *ptr, ptr);

    return 0;
}