#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main (void)
{
    // get string from user
    string s = get_string();

    // get the first character from the first string, convert to uppercase and output
    printf("%c", toupper(s[0]));

    // check if the string is longer than 1 character
    if (strlen(s) > 1) {

        // iterate over the second character to the end of the string
        for (int i = 1, n = strlen(s); i < n; i++) {

            // if the current character is a space, get the NEXT character (first letter of next word), convert to upper and print
            if (s[i] == ' ') {
                printf("%c", toupper(s[i+1]));
            }
        }
    }

    // finish off with a linefeed
    printf("\n");
}