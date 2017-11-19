#include <stdbool.h>

// alphabet is 26, adding apostrophe as special character
const int ALPHABET_SIZE = 27;

typedef struct NODE
{
    struct NODE* nodes[ALPHABET_SIZE];
    bool is_word;
} NODE;