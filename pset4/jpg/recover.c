/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

typedef uint8_t BYTE;

bool checkfile(BYTE blocks[512]);

int main(int argc, char* argv[])
{
    // check for correct number arguments. exit on error.
    if(argc != 1)
    {
        printf("Usage: ./recover\n");
        return 1;
    }

    //create infile.
    FILE* inptr = fopen("card.raw", "r");
    if(inptr == NULL)
    {
        printf("Error opening file.");
        return 2;
    }

    //initialize first file.
    FILE* outptr = NULL;

    //create buffer for names.
    char fn[8];

    //create read buffer
    BYTE buf[512];

    //initialize counter.
    int count = 0;

    //create loop to read infile.
    while(fread(buf, sizeof(BYTE), 512, inptr) != 0)
    {

        //check for magic numbers
        if(checkfile(buf))
        {
            //close if not first file.
            if(count > 0)
                fclose(outptr);

            //create file name.
            sprintf(fn, "%.3d.jpg", count);
                    
            //open file.
            outptr = fopen(fn, "w");
            if(outptr == NULL)
            {
                fclose(inptr);
                printf("could not create file.\n");
                return 3;
            }
            //write to file.
            fwrite(buf, sizeof(BYTE), 512, outptr);

            //iterate counter
            count++;
        }
        else
            //if not first file, then write.
            if(count > 0)
                fwrite(buf, sizeof(BYTE), 512, outptr);
        
    }
    // if still open close.
    if(outptr)
        fclose(outptr);
    //tidy up.
    fclose(inptr);
}

bool checkfile(BYTE blocks[512])
{
    if(((blocks[0] == 0xff) && (blocks[1] == 0xd8) && (blocks[2] == 0xff)) && ((blocks[3] == 0xe0) || blocks[3] == 0xe1))
        return true;
    else
        return false;
}
