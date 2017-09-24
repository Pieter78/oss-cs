#include <stdio.h>
#include <cs50.h>

int main(void)
{
    const int QUARTER = 25;
    const int DIME = 10;
    const int NICKEL = 5;


    printf("O hai! How much change is owed?\n");
    float amount = get_float();

    while (amount < 0) {
        printf("How much change is owed?\n");
        amount = get_float();
    }

    int amount100 = (int) (amount * 100);

    int coins = amount100 / QUARTER;
    int rest = amount100 % QUARTER;

    coins += (rest / DIME);
    rest = (rest % DIME);

    coins += (rest / NICKEL);
    rest = (rest % NICKEL);

    coins += rest;

    printf("%i", coins);
}
