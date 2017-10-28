/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // let's iterate through the values array
    for (int i = 0; i < n; i++) {

        // if we have a match, return true
        if (values[i] == value) {
            return true;
        }
    }

    // otherwise no match -> false
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{

    // Bubble sort
    // First pass, n - 1 times
    // We're comparing i with i +, so continue as long as i is equal or greater than 0
    for (int i = n - 1; i >= 0; i--)
    {
        // Second iteration for the actual comparing and swapping of elements
        for (int j = 0; j <= i; j++ )
        {
            // If the value 'left' in the array is bigger, swap the elements
            if (values[j] > values[j + 1])  {
                int temp = values[j];
                values[j] = values[j + 1];
                values[j + 1] = temp;
            }
        }
    }

    return;
}
