#include <stdio.h>
#include <string.h>
#include <cs50.h>

 int main(int argc, string argv[])
{
    if (argc<2 || argc>2)
    {
        return 1;
    
    }

    string p = GetString();
    char c;

    for (int i = 0; i < strlen(p); i++)
    {
        c = p[i];

        printf("This is a test of %c\n", c);
        
    }
}
