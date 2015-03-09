/* 
 * File:   resize.c
 * Author: djfordz
 *
 * Created on November 19, 2014, 12:03 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

#define HEADER sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)

LONG bitAdd(LONG x, LONG y);
LONG bitMultiply(LONG x, LONG n);

int main(int argc, char** argv)
{
    
    //instantiate variables
    int padding, paddingNew, xbuf;
    int n = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize [n (1 - 100)] [infile] [outfile]\n");
        return 1;
    }

    if(n < 1 || n > 100)
    {
        printf("integer out of range.\n");
        return 5;
    }

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
    BITMAPFILEHEADER bf, bfo;
    fread(&bfo, sizeof(BITMAPFILEHEADER), 1, inptr);
    
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bio;
    fread(&bio, sizeof(BITMAPINFOHEADER), 1, inptr);

    // equalize variables.
    bi = bio, bf = bfo;

    // change header info.
    bio.biWidth = bitMultiply(bio.biWidth, n);
    bio.biHeight = bitMultiply(bio.biHeight, n);

    // determine padding
    padding = (4 - ((bi.biWidth * sizeof(RGBTRIPLE)) % 4)) % 4;
    paddingNew = (padding * n) % 4;

    // temp storage
    xbuf = bitMultiply(bio.biWidth, sizeof(RGBTRIPLE));
    xbuf = bitAdd(xbuf, paddingNew);

    // determine image and file size.
    bio.biSizeImage = bitMultiply(xbuf, abs(bio.biHeight));
    bfo.bfSize = bitAdd(bio.biSizeImage, HEADER);
  
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
    fwrite(&bfo, sizeof(BITMAPFILEHEADER), 1, outptr);
  
    // write outfile's BITMAPINFOHEADER
    fwrite(&bio, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Temporary Storage
    RGBTRIPLE triple;
   
   for(int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // mark position.
        int pos = ftell(inptr);

        for(int m = 0; m < n; m++)
        {
            for(int j = 0; j < bi.biWidth; j++)
            {   
                // read scanlines
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write new scanlines
                for(int k = 0; k < n; k++)
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }

            // skip over padding
            fseek(inptr, padding, SEEK_CUR);
            
            // write padding to outfile.
            for (int k = 0; k < paddingNew; k++)
                fputc(0x00, outptr);
            
            // rewind to marked position.
            if (m < n - 1)
                fseek(inptr, pos - ftell(inptr), SEEK_CUR);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}

// add arbitrary numbers through bit manipulation.
// ref: http://stackoverflow.com/questions/4456442/interview-multiplication-of-2-integers-using-bitwise-operators
LONG bitAdd(LONG x, LONG y)
{
    if (y == 0)
        return x;
    else
        return bitAdd( x ^ y, (x & y) << 1);
}

// multiply arbitrary numbers using bit manipulation.
// ref: http://stackoverflow.com/questions/4456442/interview-multiplication-of-2-integers-using-bitwise-operators
LONG bitMultiply( LONG x, LONG n)
{
     // Initialize variables for bitwise operations.
    LONG result = 0;

    while(n != 0)
    {
        if(n & 01)
        {
            result = bitAdd(result, x);
        }

        x <<= 1;

        n >>= 1;
    }

    return result;
}
