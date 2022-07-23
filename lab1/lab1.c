#include <stdio.h>
#include <math.h>
#include <string.h>
#include "lab1.h"

double split_bill(double base_amount, double tax_rate, double tip_rate, int num_people)
{
    double total = base_amount * (1 + tax_rate) * (1 + tip_rate);
    double bill = (int)(100 * (total / num_people) + 0.9);
    return bill / 100;
}

double adjust_price(double original_price)
{
    double adjusted_price = 10 * pow(original_price, 0.5);
    return adjusted_price;
}

int sandy_eats(char menu_items[])
{
    int i;
    int len = strlen(menu_items) % 2;
    char substr[] = "fish";
    // need to check odd and fish

    if (len == 1)
    {
        return 0;
    }

    if (strstr(menu_items, substr) != NULL)
    {
        return 0;
    }

    for (i = 0; i < strlen(menu_items); i++)
    {
        if (menu_items[i] == 'j' || menu_items[i] == 'k' || menu_items[i] == 'l' || menu_items[i] == 'J' || menu_items[i] == 'K' || menu_items[i] == 'L')
        {
            return 0;
        }
    }

    return 1;
}

void imagine_fish(char thing[])
{
    char fish[] = "fish";
    strcat(thing, fish);
}