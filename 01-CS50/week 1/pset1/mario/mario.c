#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Height: ");
    int height = get_int();
    int width = 2;

    // Loop the entire height of the input
    for (int i = 0; i < height; i++) {

        // For the spaces we need width - (height + 1)
        for (int j = 0; j < ((height + 1) - width); j++) {
            printf(" ");
        }

        for (int j = 0; j < width; j++) {
            printf("#");
        }

        // Increase the width and print a line feed
        width++;
        printf("\n");


    }

}
