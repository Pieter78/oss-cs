#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Minutes: ");
    int time = get_int();
    int bottles = time * 12;

    printf("Bottles: %i\n", bottles);
}
