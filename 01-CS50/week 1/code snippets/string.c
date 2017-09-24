#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Name: ");
    string name = get_string();
    printf("Hello, %s\n", name);
}