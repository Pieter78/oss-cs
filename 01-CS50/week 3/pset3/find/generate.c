/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */

#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    // Check for correct number of arguments, if not exit program with instructions
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // get the second argument, convert the string to an integer
    int n = atoi(argv[1]);

    // if the argument count is 3, the second argument is the seed
    if (argc == 3)
    {
        // call srand48 to initiliaze seeding, using the seed provided by the user
        srand48((long) atoi(argv[2]));
    }
    else
    {
        // if not provided, use time as seed
        srand48((long) time(NULL));
    }

    // iterate n times (agument provided by user)
    for (int i = 0; i < n; i++)
    {
        // print the generated random number, times the limit
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
