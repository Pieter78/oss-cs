#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char** argv)
{
    // check if there is an argument, we only accept a single argument
    if (argc != 2)
    {
        printf("Usage: ./caesar k\n");
        return 1;

    }

    // convert the command line argument string to an int
    int k = atoi(argv[1]);


    if (k < 0) {
        printf("Your argument must be a positive integer.");
        return 1;
    }


    printf("plaintext: ");
    string s = get_string();

    char output[strlen(s)];

    for (int i = 0, n = strlen(s); i < n; i++ ) {

        int char_number = (int) s[i];

        // If it's a lower case character (96 offset)
        if (char_number >= 97 && char_number <= 122)
        {
            // Convert the character number to 1 to 26
            char_number -= 96;

            // Add k and get modulus 26 (so we keep within the 26 characters)
            char_number = (char_number + k) % 26;

            // Convert the number back to the ASCII value
            char_number += 96;
        }
        // In case it's a upper case character (65 offset)
        else if (char_number >= 65 && char_number <= 90)
        {
            // Convert the character number to 1 to 26
            char_number -= 65;

            // Add k and get modulus 26 (so we keep within the 26 characters)
            char_number = (char_number + k) % 26;

            // Convert the number back to the ASCII value
            char_number += 65;
        }

        output[i] = char_number;

    }

    printf("ciphertext: %s\n", output);
}

