#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>

int main(int argc, char* argv[])
{
    // check for correct number arguments. exit on error.
    if(argc != 1)
    {
        printf("Usage: ./recover [infile]\n");
            return 1;
    }

    //create infile.
    FILE* inptr = fopen("card.raw", "r");
   if(inptr == NULL)
   {
        printf("Could not open file\n");
        return 2;
   }

    //create buffer
    char* buf = NULL;
    int count = 0;

    //initialize buffer.
    setbuf(inptr, buf);
    setvbuf(inptr, buf, _IOFBF, 512);

    char* p;
    size_t pos;

   //create loop to read infile.
    while(fread(&buf, sizeof(buf), 1, inptr) == 1)
    {

        int mag_num[] = {0xff, 0xd8, 0xff, 0xe0, 0xe1};

        for(int i = 0; sizeof(mag_num); i++)
        {
            //check for magic numbers
            if((p = strchr(buf, mag_num[0])) != NULL)
            {
                if((p = strchr))
                pos = fseek(&buf, p, SEEK_CUR);
            }
        }
            //create file names beginning with 000.
            char* jpg = NULL;
            sprintf(jpg, "%.3d.jpg", count);

            //open file.
            FILE* filebuffer = fopen(jpg, "w");
            if(filebuffer == NULL)
            {
                printf("could not create file.");
                fclose(inptr);
                free(jpg);
                free(buf);
                return 3;
            }

            //write buffer.
            while(p != NULL)
            {
                fputs(buf, filebuffer);
                p = strchr(p + 1, mag_num);
            }



            //close file.
            fclose(filebuffer);
            free(jpg);

        //iterate count
        count++;
    }
    }
    fclose(inptr);
    free(buf);
}



