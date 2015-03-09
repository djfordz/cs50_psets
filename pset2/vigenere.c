#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>

int main (int argc, string argv[])
{
    //check CLI argument
    if (argc != 2) {
        printf("Usage: ./vigenre [keyword]\n");
        return 1;
    }
    
    //set variable
    string keyword = argv[1];

    // check keyword
    for (int i = 0, lk = strlen(argv[1]); i < lk; i++)
    {
        if (!isalpha(keyword[i]))
        {
            printf("ERROR: Keyword must be letters only.\n");
            return 1;
        }
        else
        {
            continue;
        }
    }

    // get message from user.
    string message = GetString();

    //initialize variables.
    int kl = strlen(keyword);
    int key[kl];

    //set key to 0.
    for(int j = 0; j < kl; j++)
    {
        key[j] = toupper(keyword[j]) - 'A';
    }
   
    //encrypt message
    for (int i = 0, k = 0, lm = strlen(message); i < lm; i++)
    {      
        int c = message[i];
        
        if (!isalpha(c))
        {
            printf("%c", c);
        }
        else
        {
            if (isupper(c))
            {
                int E = c + key[k % kl];

                if (E > 'Z')
                {
                    int A = c - 'A';
                    int B = (A + key[k % kl]) % 26;
                    E = B + 'A';
                }
                printf ("%c", E);
            }
            else if (islower(c))
            {
                int e = c + key[k % kl];

                if (e > 'z')
                {
                   int a = c - 'a';
                    int b = (a + key[k % kl]) % 26;
                    e = b + 'a';
                }
                printf ("%c", e);
            }
            k++;
        }
    }
    printf("\n");
}

