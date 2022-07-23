#include <stdio.h>

int main()
{
    FILE *fp = fopen("fname", 'r');
    free(fp);
    fclose(fp); //??

    // getline()

        return 0;
}