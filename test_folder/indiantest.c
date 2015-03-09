#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char* name = "ThE bESt mAN wINs";

    for(int i = 0; name[i] != '\0'; i++)
    {
        if(islower(name[i]))
            name[i] = toupper(name[i]);
        else
        {
            if(isupper(name[i]))
                if(i%2 == 0)
                    name[i]--;
                else
                    name[i] = tolower(name[i -1]);
        }
        printf("%c", name[i]);
    }
    printf("\n");
}
