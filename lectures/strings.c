#include <stdio.h>
#include <string.h>

int main()
{
    char s[100] = "some string"; // left over spots assigned \0
    // '' used for characters "" for strings

    printf("length of string from strlen() is %d\n", strlen(s));
    // strlen ends at \0

    // "some text" is a string literal and cannot be modified when passed
    // if want to change, assign char s[] = "some text", which is an array

    strcat(s, "extra");
    // str cat takes in str array and a string literal, appends to first input

    return 0;
}