#include <stdio.h>

// int main(int argc, char *argv[])
int main(int argc, char **argv)
{
    int a = argc;
    char* b = argv[0];

    printf("a: %i\n", a);
    printf("b: %s\n", b);
}