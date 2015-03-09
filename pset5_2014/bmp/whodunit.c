/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Changes red-only pixels to white while enhancing color of other pixels and writes to new file.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

void enhance(FILE* inptr, FILE* outptr);

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./whodunit infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[1];
    char* outfile = argv[2];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
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

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // enhance color bit to reveal message.
    enhance(inptr, outptr);
    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}

// Function to switch bits with 0x00 and 0xff.
void enhance(FILE* inptr, FILE* outptr)
{
    long seekptr = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    fseek(inptr, seekptr, SEEK_CUR);

    // initialize variable
    BYTE swapBit = 0;
    BYTE readBit = 0;

    // read bit
    while(fread(&readBit, sizeof(readBit), 1, inptr))
    {
        //swap bit.
        swapBit = (readBit & 8) ? 0xff : 0x00;

        // write bit.
        fwrite(&swapBit, sizeof(swapBit), 1, outptr);
    }
    
}

