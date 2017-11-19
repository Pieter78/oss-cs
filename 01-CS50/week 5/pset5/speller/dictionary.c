/**
 * Implements a dictionary's functionality.
 */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"
#include "trie.h"

// global variables
struct NODE *first_node;
int number_of_words;

// forward declare our helper functions
NODE* new_node();
int char_to_index(char c);
void unload_node(NODE* node);



/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    NODE* current_node = first_node;

    // iterate through the character string
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // check if we're pointing to NULL, if so it's not in the dictionary
        if (current_node->nodes[char_to_index(word[i])] == NULL) {
            return false;
        } else {

            // else continue
            current_node = current_node->nodes[char_to_index(word[i])];
        }
    }

    // if we haven't returned yet from return is_word
    return current_node->is_word;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // initialize our word counter
    number_of_words = 0;

    // initialize the first node
    first_node = new_node();

    // create a file pointer to read the file
    FILE *fp = fopen(dictionary, "r");

    // create a pointer to the current found for traveral
    NODE* current_node;

    // create a character array to hold the word we're working on
    char word[LENGTH+1];

    // while there are words to scan, scan next word
    while (fscanf(fp, "%s", word) == 1) {
        number_of_words++;

        // create a pointer to a node, to check where we are

        // if the first letter of the word it's pointer of the first node point to null
        // it means there is no node attached to it yet
        if (first_node->nodes[char_to_index(word[0])] == NULL)
        {
            // created the node, with children NULL, set the current pointer to it
            first_node->nodes[char_to_index(word[0])] = new_node();

            // also set the pointer in the master parent node
             current_node = first_node->nodes[char_to_index(word[0])];
        } else {

            // otherwise, simply get the pointer
            current_node = first_node->nodes[char_to_index(word[0])];
        }

        // for each next letter in the word
        for (int i = 1, n = strlen(word); i < n; i++)
        {

            if (current_node->nodes[char_to_index(word[i])] == NULL)
            {
                // create a new node at the current position
                current_node->nodes[char_to_index(word[i])] = new_node();

                // also set the current node to the
                current_node = current_node->nodes[char_to_index(word[i])];
            } else
            {
                // otherwise, simply get the pointer
                current_node = current_node->nodes[char_to_index(word[i])];
            }
        }

        current_node->is_word = true;
    };

    // close the file pointer
    fclose(fp);


    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return number_of_words;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    unload_node(first_node);

    return true;
}


/**
 * HELPER FUNCTIONS
 */


void unload_node(NODE* node)
{
    // set all the pointers of the new node to NULL
    for (int i = 0; i < 27; i++)
    {
        if (node->nodes[i] != NULL)
        {
            unload_node(node->nodes[i]);
        }
        else
        {
            free(node->nodes[i]);
        }
    }

    free(node);
}

// initialize a new node, with all children pointing to null
NODE* new_node()
{
    // allocate memory and get a pointer
    NODE *new_node = calloc(1, sizeof(NODE));

    // set all the pointers of the new node to NULL
    for (int i = 0; i < 26; i++)
    {
        // set child to NULL
        new_node->nodes[i] = NULL;
        new_node->is_word = false;
    }

    // return the fresh node
    return new_node;
}

int char_to_index(char c)
{
    // check if it's an apostrophe, if so return our reserved index of 26, if not, convert the character to an int from 0 to 25
    if (c == '\'') return 26;
    else return (int) tolower(c) - 97;
}
