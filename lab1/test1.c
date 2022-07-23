#include <stdio.h>
#include "lab1.h"

int main()
{
    double test1 = split_bill(50.01, 0.13, 0.15, 2);
    printf("%.2f\n", test1);
    // fix rounding

    double test2 = adjust_price(25.00);
    printf("%.2f\n", test2);

    int test3 = sandy_eats("nopefinn");
    printf("%d\n", test3);

    char test4[] = "zebra";
    imagine_fish(test4);
    printf("%s", test4);

    return 0;
}