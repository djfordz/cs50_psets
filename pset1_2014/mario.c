#include <stdio.h>
#include <cs50.h>

int main (void) 
{
    int height = 0;
    
   // repeat question if height outside of set.
   do 
   {
            printf ("How high would you like to build your half-pyramid?\n (enter a number between 1 and 23)\n");
            height = GetInt();
            
   } while (height < 0 || height > 23);
   
    // Build pyramid
    for (int i = 0, h = height; i < h; i++) 
    {
    
        for (int k = height - 1; k > i; k--) 
        {
            printf(" ");
        }
        
        for (int j = 0; j < i; j++) 
        {
            printf("#");
        }
       
        printf("##\n");
    }
}
