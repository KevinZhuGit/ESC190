// time complexity

/*
EXAMPLE: inserting into dynamic array at index i

- if there is space:
    - inserting at front will be O(n) moves, moves everything right one
    - inserting at back is O(1)
    - general insert at i: O(n - i)

- not enough room, need to realloc
    - realloc is O(n)                                                   // realloc frees old memory coppied over
    - then need to insert in new list, taking same moves as above
        - n + (n-i) = O(n), drop constants


void insert(int** arr , int *max, int *curr, int index, int val)     // NEED DOUBLE POINTER FOR ARR
{
    // check len and resized if needed
    if (max == curr)
    {
        *arr = realloc(arr, sizeof(int) * (max *2 ));
        *max = (*max) * 2
    }

    //insert
    for (int i = curr; i > index; i--)                        // WORKS FROM BACK
    {

    }

    (*arr)[index] =
}



*/
