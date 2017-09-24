#include <stdio.h>
#include <cs50.h>

int main(void)
{
//     int i = get_int();
//     if (i < 0)
//     {
//         printf("Negative\n");
//     } else if (i > 0)
//     {
//         printf("Positive\n");
//     } else if (i == 0)
//     {
//         printf("Zero\n");
//     }

    char c = get_char();
    if (c == 'y' || c == 'Y')
    {
        printf("yes\n");
    } else if (c == 'n' || c == 'N')
    {
        printf("no\n");
    } else
    {
        printf("error\n");
    }

}