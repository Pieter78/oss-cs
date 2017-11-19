/**
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>


#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize factor infile outfile\n");
        return 1;
    }

    // remember filenames
    int factor = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    printf("%i\n", factor);

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // total file size
    printf("bfSize: %x (%u)\n", bf.bfSize, bf.bfSize);

    // total header size
    int header_size = (int) sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    printf("header size: %x (%u)\n", header_size, header_size);

    // total image size
    printf("biSizeImage: %x (%u)\n", bi.biSizeImage, bi.biSizeImage);

    // width
    printf("biWidth: %x (%u)\n", bi.biWidth, bi.biWidth);

    // negative height
    printf("biHeight: %i\n", bi.biHeight);

    // RGBTriple is 3 bytes
    printf("RGB Triple: %x (%u)", (int) sizeof(RGBTRIPLE), (int) sizeof(RGBTRIPLE));



    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // manipulate the header of the output file with the new dimensions
    int new_biWidth = bi.biWidth * factor;
    int new_biHeight = bi.biHeight * factor;

    // determine the new padding
    int new_padding = (4 - (new_biWidth * sizeof(RGBTRIPLE)) % 4) % 4;;

    // determine the new biSizeImage (image size)
    int new_biSizeImage = ((new_biWidth * sizeof(RGBTRIPLE)) + new_padding) * abs(new_biHeight);

    // determine the new bfSize (file size)
    int new_bfSize = new_biSizeImage + header_size;

    printf("\n\nnew_width: %i\nnew_height: %i\nnew_padding: %i\n", new_biWidth, new_biHeight, new_padding);
    printf("\nnew_biSizeImage: %i", new_biSizeImage);
    printf("\nnew_bfSize: %i", new_bfSize);

    int original_width = bi.biWidth;
    int original_height = bi.biHeight;

    bi.biWidth = new_biWidth;
    bi.biHeight = new_biHeight;

    bi.biSizeImage = new_biSizeImage;
    bf.bfSize = new_bfSize;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // create a buffer where we can put the lines in
    RGBTRIPLE *buffer = malloc(sizeof(RGBTRIPLE) * new_biWidth + new_padding);

    // determine padding for scanlines
    int padding = (4 - (original_width * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(original_height); i < biHeight; i++)
    {
        // iterate over pixels in scanline, but factor times
        for (int j = 0; j < original_width; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            // fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

            for (int f = 0; f < factor; f++)
            {
                buffer[j * factor + f] = triple;
            }


        }

        for (int f = 0; f < factor; f++)
        {
            fwrite(buffer, sizeof(RGBTRIPLE) * new_biWidth, 1, outptr);

            // add new padding to output file
            for (int k = 0; k < new_padding; k++)
            {
                fputc(0x00, outptr);
            }
        }

        // skip over padding of input file, if any
        fseek(inptr, padding, SEEK_CUR);


    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    free(buffer);

    // success
    return 0;
}
