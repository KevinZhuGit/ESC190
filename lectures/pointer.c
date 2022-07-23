#include <stdio.h>
#include <stdlib.h>

void change_int(int *ptr_x) // passed in address so ptr_x is a pointer to value
{
    // need to pass address in, if int is passed it creates local copy
    *ptr_x = 50;
}

void change_array_size(char *ptr) // pass in array || HAS ERROR
{
    ptr = realloc(ptr, sizeof(char) * 100);
}

int main()
{
    // * symbol declares pointer
    int *x; // x is a pointer to an int that stores an address

    // & gives adrress, * gets value of address it points to
    int a = 100;
    int *ptr_a = &a;       // pointer that stores location of a
    int **pptr_a = &ptr_a; // ** dereferences twice so pptr_a can retrieve value stored in a
    // pointers get assigned a new chunk of memory too

    // DYNAMIC ARRAYS //
    int *x = malloc(sizeof(int) * 5); // malloc sets out space, assigns random ints
    // x points to first address in the array, given at least size of 5 ints rn
    // can access other elements through x+1, x+2, int* tells that next element is size int away (moves by int steps)
    // or can do x[0], x[1]...

    // calloc(sizeof()* n) gives 0's instead of rand nums

    // realloc(pointer, sizeof() * n), reallocates size of pointer
    // copies over values in pointer, and recreates in new space?

    // memory allocated by malloc, calloc, need to be manually freed
    // free(x)

    return 0;
}