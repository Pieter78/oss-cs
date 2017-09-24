#include <stdio.h>
#include <cs50.h>

int main(void)
{
    char c = get_char();


    switch (c)
    {
        case 'y':
        case 'Y':
            printf("Yes");
            break;

        case 'n':
        case 'N':
            printf("No");
            break;

        default:
        printf("Error!");
            break;
    }
}