#include <stdio.h>
#include <cs50.h>

void print_name(string name);

int main(void)
{
    string s = get_string();
    print_name(s);
}

void print_name(string name)
{
    printf("hello, %s\n", name);
}


