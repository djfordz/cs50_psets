#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void) 
{

float input = 0;
int quarter = 0, dime = 0, nickel = 0, penny = 0, numCoins = 0, change = 0;

// Ask for input, check for only positive float, if negative repeat.
    do 
    {
            printf ("O hai! How much change is owed?\n");
            input = GetFloat();
    } while (input <= 0);

    // Convert (float) input to (int) change
    input = roundf(input * 100);
    change = input;
    
    // Check change in each category and decrease by amount.
    while (change > 0) 
    {
        if (change >= 25) 
        {
            change = change - 25;
            quarter++;
        }
        else if (change >= 10 && change < 25) 
        {
            change = change - 10;
            dime++;
        }
        else if (change >= 5 && change < 10) 
        {
            change = change - 5;
            nickel++;
        }
        else if (change > 0  && change < 5) 
        {
            change = change - 1;
            penny++;
        }
    }
   
   // Add number of coins. 
   numCoins = quarter + dime + nickel + penny;
   
   printf ("%d\n",numCoins);

}

