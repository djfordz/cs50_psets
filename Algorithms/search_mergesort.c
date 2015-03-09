#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

#define MAX 65536

//prototypes
void mergeSplit(int left, int right, int* values);
void merge(int* values, int l_start, int l_end, int r_start, int r_end);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n) {

    if(n > 2) {
        n /= n;
        search(value, values, n);
    }
        
    if(values[n] == value)
        //return true if found.
        return true;
    else
        //return false if not found.
        return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n) {

    mergeSplit(0, n, values);
}


void mergeSplit(int left, int right, int* values) {

    if(right - left <= 1)
        return;

    int l_start = left;
    int l_end = (left + right) / 2;
    int r_start = l_end;
    int r_end = right;

    mergeSplit(l_start, l_end, values);
    mergeSplit(r_start, r_end, values);
    merge(values, l_start, l_end, r_start, r_end);
}

void merge(int* values, int l_start, int l_end, int r_start, int r_end) {

// temporary list sizes
    int l_len = l_end - l_start;
    int r_len = r_end - r_start;
 
    // temporary lists for comparison
    int l_half[l_len];
    int r_half[r_len];
 
    int i, l, r;
 
    // copy values into temporary lists
    for (i = l_start, l = 0; i < l_end; i++, l++) {
        l_half[l] = values[i];
    }
    for (i = r_start, r = 0; i < r_end; i++, r++) {
        r_half[r] = values[i];
    }
 
    // merge the values back into positions in main list 
    for (i = l_start, r = 0, l = 0; l < l_len && r < r_len; i++) {
        // if left value < r value, move left value
        if (l_half[l] < r_half[r]) {
            values[i] = l_half[l]; l++;
        }
        // else move right value
        else {
            values[i] = r_half[r]; r++;
        }
    }
 
    // handle leftover values
    for ( ; l < l_len; i++, l++) {

        values[i] = l_half[l]; 
    }

    for ( ; r < r_len; i++, r++) {

        values[i] = r_half[r];
    }
}
