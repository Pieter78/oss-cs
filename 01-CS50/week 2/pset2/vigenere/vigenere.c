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
        printf("Usage: ./vigenere k\n");
        return 1;

    }

    // create a string of size argv[1]
    char* key = argv[1];

        // convert the input string (argv[1]) to lower case

    for (int i = 0; i < strlen(key); i++ ) {

        // convert to lower case
        key[i] = tolower(key[i]);

        // check if it's actually a letter (a-z) otherwise return with an error
        int char_number = (int) key[i];

        if (char_number < 97 || char_number > 122) {
            printf("error: the key should only contain letters (a to z).");
            return 1;
        }

    }

    // get the plaintext input from the user
    printf("plaintext: ");
    string s = get_string();

    // create our output string
    char output[strlen(s)];

    // create a counter for the key
    int key_counter = 0;

    // iterate through the input string
    for (int i = 0, n = strlen(s); i < n; i++ ) {

        // cast the letter on position i to a character number, same for the letter on position key_counter for the key
        int char_number = (int) s[i];
        int key_number = (int) key[key_counter] - 97;

        // If it's a lower case character (96 offset)
        if (char_number >= 97 && char_number <= 122)
        {
            // Convert the character number to 1 to 26
            char_number -= 96;

            // Add k and get modulus 26 (so we keep within the 26 characters)
            char_number = (char_number + key_number) % 26;

            // Convert the number back to the ASCII value
            char_number += 96;

            // increment the key counter
            key_counter++;

            // if the key counter is the length of the key, reset it to 0
            if (key_counter == strlen(key)) {
                key_counter = 0;
            }
        }
        // In case it's a upper case character (65 offset)
        else if (char_number >= 65 && char_number <= 90)
        {
            // Convert the character number to 1 to 26
            char_number -= 65;

            // Add k and get modulus 26 (so we keep within the 26 characters)
            char_number = (char_number + key_number) % 26;

            // Convert the number back to the ASCII value
            char_number += 65;

            // increment the key counter
            key_counter++;

            // if the key counter is the length of the key, reset it to 0
            if (key_counter == strlen(key)) {
                key_counter = 0;
            }
        }

        // write to the output
        output[i] = char_number;
    }

    // output result
    printf("ciphertext: %s\n", output);
}

