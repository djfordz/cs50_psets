#ifndef DICTHELP_H
#define DICTHELP_H

#include <stdio.h>
#include <dictionary.h>

#define SSIZE 20
#define EMPTY_LIST NULL
#define TABLE_SIZE 256
#define SHIFT_AMT 8 * sizeof(unsigned int) - TABLE_BITS
#define TABLE_BITS 8

typedef struct  Word
{
	char word[LENGTH];
}Word;

typedef struct WordList
{
	struct Word *word;
	struct WordList *next;
} WordList;

