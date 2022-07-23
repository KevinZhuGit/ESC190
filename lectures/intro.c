// directives
#include <stdio.h> //has basic c functions included like printf
// declarations of functions, initializes functions
int add(int x, int y);

// what gets run is the in main function
int main()
{
    printf("hi\n");
    printf("hi %s", "nah\n");

    int z; // will take random numbers to allocate space (bits)
    int q;
    printf("%d %d", z, q);

    if (z || q > 0) // need to update c to get or?
    {
        printf("true");
    }

    if (200) // 0 is false, everything else is true
    {
        printf("still true");
    }

    // VARIABLES
    // variable type must be declared (type never changes)
    int x;
    x = 0;     // must declare first then assign, because needs to know min space allocated
    int y = 0; // declaration and assignment in one step

    // TYPES
    unsigned char c = 'b'; // char types are ints, stored through asci as number
    // printf("%c %hhu", c, c); // %c tells to render as char, %hhu renders as the number
    char name[] = "alskjdd"; // terminate by /0

    return 0;
}

// manually compiling do gcc 'filename' which complies
// ./filename to run the compiled file

// what is valgrind for????

// FUNCTIONS
// have to declare return type first, declare parameter types
int add(int x, int y)
{
    int z = x + y;
    return z;
}
// to prevent compiling warnings, add header declarations
