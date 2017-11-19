#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: ./recover filename");
    }

    // remember filenames
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");

    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // initiliaze 512 bytes for reading the file
    char *file_block = malloc(512 * sizeof(char));

    // read 512 bytes from file
    fread(file_block, 512 * sizeof(char), 1, inptr);

    // counter for filenames
    int counter = 0;

    // create pointer for filenames, format has to be ???.jpg, so we know the size
    char *file_name = malloc(7 * sizeof(char));

    // reserve a pointer for the output false
    FILE *outptr;

    // keep track of state here
    bool writing = false;

    do {
        int sum = 0;

        // check if the block is 'zeroed', if so assume end of file
        for (int i = 0; i < 512; i++)
        {
            sum |= file_block[i];
        }

        // if it is zeroed and we're writing, stop writing and continue the loop
        if (sum == 0 && writing == true)
        {
            writing = false;
            fclose(outptr);
            continue;
        }

        // otherwise if it is zeroed, continue as well, we know we don't have to write and there is no sense in checking for headers
        else if (sum == 0 && writing == false)
        {
            continue;
        }

        // if true, a jpeg has started, open a file and start writing
        if (file_block[0] == (char) 0xff && file_block[1] == (char) 0xd8 && file_block[2] == (char) 0xff && file_block[3] >= (char) 0xe0) {

            // set writing state
            writing = true;

            // create the file name
            sprintf(file_name, "%03d.jpg", counter);

            // open output file
            outptr = fopen(file_name, "w");

            // check if an error occured
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", file_name);
                return 3;
            }

            // print the file name saved
            printf("%s\n created..", file_name);

            // increase the counter for the next file found
            counter++;
        }

        // if we are writing, write the buffer to the file
        if (writing) {
            fwrite(file_block, 512 * sizeof(char), 1, outptr);
        }

    // continue while fread can read data
    } while (1 == fread(file_block, 512 * sizeof(char), 1, inptr));

    // free memory from mallocs
    free(file_block);
    free(file_name);

}