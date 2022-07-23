#include <stdlib.h>

void change_array_size(int *x) // passes on address of pointer
{
    x = realloc(x, sizeof(int) * 5); // does not modify x in main scope, need to return
    // realloc recreates array in new memory spot, local x is given the address of new array
    // the array previously held is deallocated, so calling x in main scope will call memory block not held -> errors
}

void better_change_array_size(int **x)
{
    *x = realloc(x, sizeof(int) * 5);
    // do we need to free here? / do we need to free realloc
}

int main()
{

    int *x = malloc(sizeof(int) * 2);
    change_array_size(x);
    better_change_array_size(&x);
    free(x);
    // free(x); double free() can cause error

    //
    int **z = malloc(sizeof(int *) * 5);
    for (int i = 0; i < 5; i++)
    {
        *(z + i) = calloc(i, sizeof(int)); // creates allocated sub arrays that need to be freed
    }

    for (int i = 0; i < 5; i++)
    {
        free(*(x + i)); // frees sub arrays previously assigned
    }

    free(z); // doesnt free sub arrays alone, only get rid of addresses in and of x

    return 0;
}