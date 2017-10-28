/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void swap(int x1, int y1, int x2, int y2);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        // clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    // We need one free space, so we start count one less
    // The last one will automatically be 0
    int number_of_elements = (d * d) - 1;

    // Initialize a counter to act as the value
    int counter = number_of_elements;

    for (int y = 1; y <= d; y++) {
        for (int x = 1; x <= d; x++) {
            board[x][y] = counter;
            counter--;
        }
    }

    // Check if the number of elements is odd, in that case, swap the last two elements
    if (number_of_elements % 2 != 0) {

        // Swap the elements
        swap(d - 1, d, d - 2, d);
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // Iterate through the dimensios
    for (int y = 1; y <= d; y++) {
        for (int x = 1; x <= d; x++) {
            if (board[x][y] < 10) {
                // Add an extra space in case of a 1-digit number
                printf(" %i ", board[x][y]);
            } else {
                printf("%i ", board[x][y]);
            }
        }
        // Print a linefeed for the next line
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{

    // First determine where the x and y are of the tile
    // Initialize x and y outside of the for-loop for later use
    int x, y;
    int legalMove = false;

    for (y = 1; y <= d; y++) {
        for (x = 1; x <= d; x++) {
            if (board[x][y] == tile) {

                // Using goto instead of break, since we have two nested loops
                goto found;
            }
        }
    }

    found:
    // check tile above, if y != 1
    if (y != 1) {
        if (board[x][y - 1] == 0) {
            swap(x, y, x, y - 1);
            legalMove = true;
        }
    }

    // check tile below, if y != d
    if (y != d) {
        if (board[x][y + 1] == 0) {
            swap(x, y, x, y + 1);
            legalMove = true;
        }

    }

    // check tile left, if x != 1
    if (x != 1) {
        if (board[x - 1][y] == 0) {
            swap(x, y, x - 1, y);
            legalMove = true;
        }
    }

    // check tile right, if x != d
    if (x != d) {
        if (board[x + 1][y] == 0) {
            swap(x, y, x + 1, y);
            legalMove = true;
        }
    }

    return legalMove;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    // if we go left to right, top to bottom, every value we encounter should be smaller than the next
    int checkValue = board[1][1];

    for (int y = 1; y <= d; y++) {
        for (int x = 1; x <= d; x++) {
            // skip the initial value
            if (x == 1 && y == 1) {
                continue;
            }

            if (checkValue > board[x][y]) {
                return false;
            }
        }
    }

    return true;
}

void swap (int x1, int y1, int x2, int y2) {

        int temp = board[x1][y1];
        board[x1][y1] = board[x2][y2];
        board[x2][y2] = temp;
}
