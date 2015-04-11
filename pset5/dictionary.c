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
#include <ctype.h>

#include "dictionary.h"

// prototypes
HASHREC **inithashtable();
void deletehashtable(HASHREC **ht);
HASHREC *hashsearch(HASHREC **ht, const char *w);
void hashinsert(HASHREC **ht, const char *w);
void hashdelete(HASHREC **ht, const char *w);
unsigned int bitwisehash(const char *word, int tsize, unsigned int seed);
int scmp(char *s1, const char *s2);

// declare global variable for size of dictionary.
unsigned int numwords = 0;

// declare global variable for hash table, due to pset restrictions.
HASHREC **word_table;
HASHREC *htmp, *hprv;
char *word;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word) {

  // initialize variables.
  char *tempword = (char *)malloc(sizeof(char *) * LENGTH + 1);
  int index = 0;

  // make word lowercase.
  for(int c = 0; c < strlen(word); c++) {
    tempword[c] = tolower(word[c]);
    index++;
  }

  // check words.
  if(hashsearch(word_table, tempword) != NULL) {
    return true;
  }
  else {
    return false;
  }
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char *dictionary) {
  // open dictionary file.
  FILE *inptr;
  inptr = fopen(dictionary, "r");
  if (inptr == NULL) {
    perror("Could not open file.");
    return false;
  }

  // Initialize hash table
  word_table = inithashtable();

  // declare variables.
  int index = 0; char c; 
  word = (char *)malloc(sizeof(char *) * LENGTH + 1);

  // read word from file.
  for(c = fgetc(inptr); c != EOF; c = fgetc(inptr)) {
    word[index] = c;
    index++;

    if(c == '\n') 
    {
      word[index -1] = '\0';
      hashinsert(word_table, word);
      numwords++;
      index = 0;
    }
  }

  fclose(inptr);
  
  if (word_table != NULL)
    return true;
  else
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size() {
  // return number of words in dictionary.
  return numwords;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void) {
  //hashdelete(word_table, initword);
  deletehashtable(word_table);
  free(word);
    return true;

}

// Create hash table, initialize pointers to NULL 
HASHREC **inithashtable() {
  int i;
  HASHREC **ht;
  ht = (HASHREC **)malloc(sizeof(HASHREC *) * TSIZE);

  for(i = 0; i < TSIZE; i++) 
    ht[i] = (HASHREC *)NULL;

  return (ht);
}
void deletehashtable(HASHREC **ht) {

//  while(htmp != NULL) {
//     htmp = hprv;;
//    hprv = hprv->next;
//    free(htmp);
//  }
  int i;
  for(i = 0; i < sizeof(ht); i++) {
    free(ht[i]);
  }
  free(ht);
}
// Search hash table for given string, return record if found, else NULL 
HASHREC *hashsearch(HASHREC **ht, const char *w) {

  unsigned int hval = HASHFN(w, TSIZE, SEED);

  for(hprv = NULL, htmp = ht[hval]; htmp != NULL && scmp(htmp->word, w) != 0;
       hprv = htmp, htmp = htmp->next) {
    ;
  }
  if(htmp == NULL)
    return htmp;
  if (hprv != NULL) // move to front on access 
    {
      hprv->next = htmp->next;
      htmp->next = ht[hval];
      ht[hval] = htmp;
    }

  return htmp;
}

// Search hash table for given string, insert if not found.
void hashinsert(HASHREC **ht, const char *w) {

  unsigned int hval = HASHFN(w, TSIZE, SEED);

  for(hprv = NULL, htmp = ht[hval]; htmp != NULL && scmp(htmp->word, w) != 0;
       hprv = htmp, htmp = htmp->next) {
    ;
  }

  if (htmp == NULL) {
    htmp = (HASHREC *)malloc(sizeof(HASHREC));

    htmp->word = (char *)malloc(strlen(w) + 1);

    strcpy(htmp->word, w);

    htmp->next = NULL;

    if (hprv == NULL) {
      ht[hval] = htmp;
    }
    else
      hprv->next = htmp;

    // new records are not moved to front
  } else {
    if (hprv != NULL) // move to front on access 
    {
      hprv->next = htmp->next;
      htmp->next = ht[hval];
      ht[hval] = htmp;
    }
  }

  return;
}
void hashdelete(HASHREC **ht, const char *w) {

  HASHREC *htmp, *hprv;
  unsigned int hval = HASHFN(w, TSIZE, SEED);

  for(hprv = NULL, htmp = ht[hval]; htmp != NULL && scmp(htmp->word, w) != 0;
       hprv = htmp, htmp = htmp->next) {
    ;
  }

  while(hprv != NULL) // move to front on access 
    {
      htmp = hprv;
      hprv = hprv->next;
      free(htmp);

    }

 
}
unsigned int bitwisehash(const char *word, int tsize, unsigned int seed) {
  char c;
  unsigned int h;

  h = seed;
  for (; (c = *word) != '\0'; word++) {
    h ^= ((h << 5) + c + (h >> 2));
  }
  return ((unsigned int)((h & 0x7fffffff) % tsize));
}

int scmp(char *s1, const char *s2) {
  while (*s1 != '\0' && *s1 == *s2) {
    s1++;
    s2++;
  }
  return (*s1 - *s2);
}
