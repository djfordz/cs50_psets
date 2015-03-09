/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

//prototypes
HASHREC **inithashtable();
HASHREC *hashsearch(HASHREC **ht, char *w);
void hashinsert(HASHREC **ht, char *w);
unsigned int bitwisehash(char *word, int tsize, unsigned int seed);
int scmp( char *s1, char *s2 );

//declare global variable for size of dictionary.
unsigned int numwords = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    char *word_check = (char)malloc(sizeof(char) * LENGTH + 1);

    
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
	// open dictionary file.
   	FILE* inptr;
   	inptr = fopen(dictionary, "r");
    if(inptr == NULL)
    {
        perror("Could not open file.");
        return false;
    }

    //Initialize word ptr.
    char *word = malloc(sizeof(char) * LENGTH + 1);

    //Initialize hash table
    HASHREC **word_table = inithashtable();

    // read in each word in file.
    while(fgets(word, LENGTH, inptr) != NULL)
    {
        hashinsert(word_table, word);
    }

    numwords = sizeof(word_table);

    if(word_table != NULL)
        return true;
    else
        return false;

}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size()
{
    //return number of words in dictionary.
    return numwords;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}



/* Create hash table, initialise ptrs to NULL */
HASHREC **inithashtable()
{
    int i;
    HASHREC **ht;

    ht = (HASHREC **) malloc( sizeof(HASHREC *) * TSIZE );

    for( i=0 ; i<TSIZE ; i++ )
        ht[i] = (HASHREC *) NULL;

    return(ht);
}

/* Search hash table for given string, return record if found, else NULL */
HASHREC *hashsearch(HASHREC **ht, char *w)
{
    HASHREC *htmp, *hprv;
    unsigned int hval = HASHFN(w, TSIZE, SEED);

    for( hprv = NULL, htmp=ht[hval]; htmp != NULL && scmp(htmp->word, w) != 0; hprv = htmp, htmp = htmp->next)
    {
        ;
    }

    if( hprv!=NULL ) /* move to front on access */
    {
    hprv->next = htmp->next;
    htmp->next = ht[hval];
    ht[hval] = htmp;
    }

    return(htmp);
}


/* Search hash table for given string, insert if not found */
void hashinsert(HASHREC **ht, char *w)
{
    HASHREC *htmp, *hprv;
    unsigned int hval = HASHFN(w, TSIZE, SEED);

    for( hprv = NULL, htmp=ht[hval]; htmp != NULL && scmp(htmp->word, w) != 0; hprv = htmp, htmp = htmp->next )
    {
        ;
    }

    if( htmp==NULL )
    {
        htmp = (HASHREC *) malloc( sizeof(HASHREC) );

        htmp->word = (char *) malloc( strlen(w) + 1 );

        strcpy(htmp->word, w);

        htmp->next = NULL;

        if( hprv==NULL )
            ht[hval] = htmp;
        else
            hprv->next = htmp;

        /* new records are not moved to front */
    }
    else
    {
        if( hprv!=NULL ) /* move to front on access */
        {
            hprv->next = htmp->next;
            htmp->next = ht[hval];
            ht[hval] = htmp;
        }
    }

    return;
}

unsigned int bitwisehash(char *word, int tsize, unsigned int seed)
{
    char    c;
    unsigned int h;

    h = seed;
    for( ; ( c=*word )!='\0' ; word++ )
    {
    h ^= ( (h << 5) + c + (h >> 2) );
    }
    return((unsigned int)((h&0x7fffffff) % tsize));
}

int scmp( char *s1, char *s2 )
{
    while( *s1 != '\0' && *s1 == *s2 )
    {
    s1++;
    s2++;
    }
    return( *s1-*s2 );
}
