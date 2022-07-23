#include <stdio.h>
#include <stdlib.h>

int main()
{

    char *ptr = malloc(sizeof(char) * 5);
    *ptr = "abcde";

        return 0;
}