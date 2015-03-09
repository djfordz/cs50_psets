/***
  * whodunit.c
  * 
  * Computer Science 50
  * Problem Set 4
  *
  * Manipulates colors of image to enhance hidden content.
  *
  ***/

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
  //ensure proper usage.
  if(argc != 3)
  {
    printf("Usage: ./whodunit <infile> <outfile>.\n");
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

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // initialize variable
    BYTE readBit = 0;

    // read bit
    while(fread(&readBit, sizeof(readBit), 1, inptr))
    {
        //swap bit.
        BYTE swapBit = (readBit & 8) ? 0xff : 0x00;

        // write bit.
        fwrite(&swapBit, sizeof(swapBit), 1, outptr);
    }
    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

}
