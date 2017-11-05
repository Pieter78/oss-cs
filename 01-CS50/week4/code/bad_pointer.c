#include <string.h>
#include <stdio.h>

// won't run

void foo(char *bar)
{
    char c[12];
    memcpy(c, bar, strlen(bar));
}

int main (int argc, char *argv[])
{
    foo(argv[1]);
    printf("%i", argc);
}