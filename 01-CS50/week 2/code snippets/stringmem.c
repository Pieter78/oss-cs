#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string s = "teststring\0\0\0\0";
    int i = 0;

    while (i != 255)
    {
        printf("%c", s[i]);
        i++;

    };
}