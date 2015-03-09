/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"
#define MAX 65536

int splitp(int n, int factor);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int factor = 2;
    n = splitp(n, factor);

    for (int i = 0; i < n + 1; i++)
    {
        if (value == values[n])
        {
            return true;
        }
        else if (value < values[n])
        {
            n = splitp(n, factor);

            if (value == values[n])
            {
                return true;
            }
        }
        else if (value > values[n])
        {
            n += 1;

            if (value == values[n])
            {
                return true;
            }
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for(int i = 0, j = n; i < j; i++)
    {
        for(int k = i + 1; k < j; k++)
        {
            if(values[i] > values[k])
            {
                int tmp = values[i];
                values[i] = values[k];
                values[k] = tmp;
            }
            else
            {
                continue;
            }
        }
    }
}

int splitp(int n, int factor)
{
    n /=  factor;

    return n;
}
