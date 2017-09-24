#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    // ask user for input
    string s = get_string();

    // make sure s get_string returned a string
    if (s != NULL) {

        // iterate over the characters in s one at a time
        for (int i = 0, n = strlen(s); i < n; i++)
        {
            // print i'th character of s
            printf("%c\n", s[i]);
        }

    }

}