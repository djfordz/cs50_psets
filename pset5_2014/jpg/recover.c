/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

typedef uint8_t BYTE;

typedef struct
{
    BYTE data[512];
}BLOCK;

#define ONE     0xFF
#define TWO     0xD8
#define THREE   0xFF
#define D807    0xDB
#define JFIF    0xE0
#define EXIF    0xE1
#define CANON   0xE2
#define D500    0xE3
#define SPIFF   0xE8
#define TRAIL   0xD9
#define ALEN(x)   (sizeof(x) / sizeof(x[0]))


int main(int argc, char** argv)
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover infile\n");
        return 1;
    }

    // remember filename
    char* infile = argv[1];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // create temp file
    FILE* buffer = tmpfile();
    if (buffer == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", buffer);
        return 3;
    }

    // temp storage.
    BLOCK *buf = malloc(sizeof(BLOCK));

    //counter
    int count = 0;
    char filenum[4];
   
     while(fread(&buf, sizeof(BLOCK), 1, inptr) == NULL)
    {

        long pos = ftell(inptr);

            if((char)buf.data[0] + (char)buf.data[1] + (char)buf.data[2] == MAGIC_NUM)
            {
                switch(buf.data[3])
                {
                    case D807: 
                    break;
                    case JFIF:
                    break;
                    case EXIF:
                    break;
                    case CANON:
                    break;
                    case D500:
                    break;
                    case SPIFF:
                    break;
                }
                
                sprintf(filenum, "%03d", count)
                FILE* outptr = fopen(filenum, "w");
                while(buf.data != TRAIL)
                {
                    fwrite(&buf, sizeof(BLOCK), 1, buffer);
                }
                count++;
            }
    }
        


        
    
}
