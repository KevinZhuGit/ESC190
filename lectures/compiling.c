#include <stdio.h>

int main()
{
    int a = 7;
    int b = 6;
    int c = a + b;

    printf("%d\n", c);

    double result = (int)(a + 0.5);
    // result has memory allocation of double, however, answer will be rounded down due to int
    printf("%lf", result);

    return 0;
}

// gcc test.c will create a.exe automatically if no specific output
// everytime gcc test.c will update a.exe
// can run using ./a or ./a.exe, ./ will look for the exe file

// to specify output use gcc test.c -o teste.exe

// cd = cd .
// cd .. takes you back to parent
// cd ~ takes you to home

// pwd gives path

// ls lists content of curr folder
// ls <path> gives you list in path
// ./ is just saying in reference to where you are, dont need, can just say name

// mkdir <name>