#include <cs50.h>
#include <stdio.h>

int get_positive_int(void);

int main(void)
{
    int change = 0;

    int change_owed = get_positive_int();

    int quarters = change_owed / 25;
    change_owed -= (25 * quarters);

    int dimes = change_owed / 10;
    change_owed -= (10 * dimes);

    int nickels = change_owed / 5;
    change_owed -= (5 * nickels);

    change = quarters + dimes + nickels + change_owed;

    printf("%i\n", change);
}

int get_positive_int(void)
{
    int n;
    do
    {
        n = get_int("Change owed: ");
    }
    while (n < 1);
    return n;
}
