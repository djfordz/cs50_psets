#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

 //prototypes
 int cmp_name(const void *a, const void *b);
 unsigned int str_to_int(const char *str);
 unsigned hash(Word *word);
 void add_entry(WordList *a);
 WordList retrieve(Word *word);
char *freadname(void *ptr, int len, FILE* stream);

//create hash table (4 * 256 Bytes long) and set to NULL.
static WordList word_ht[TABLE_SIZE];

unsigned int str_to_int(const char *str)
{
	unsigned value = 0u, tmp = 0u;
	int size = sizeof(int) / sizeof(char);
	int len = strlen(str);

	while(len >= size)
	{
		value ^= *(unsigned *)str;
		str += size;
		len -= size;
	}

	if(len > 0)
	{
		strcpy((char *)&tmp, str);
		value ^= tmp;
	}

    return value;
}


//hashing method
unsigned hash(Word *word)
{
    //declare variables to use.
	char hash_string[LENGTH];
	unsigned int val;

    //write word into string.
	sprintf(hash_string, "%s", (char *)word);

    //convert string to int.
	val = str_to_int(hash_string);

    //return hashed word.
	return (val >> SHIFT_AMT);
}

struct WordList retrieve(Word *word)
{
	WordList list_a = word_ht[hash(word)];

	for( ; list_a != NULL; list_a = list_a->next)
		if(cmp_name(word, list_a->word) == 0)
			return list_a;

	return EMPTY_LIST;
}

void add_entry(WordList *a)
{
	WordList b = retrieve(a->word);

	unsigned hashcode;

	if(b != EMPTY_LIST)
	{
		a->next = b->next;
		*b = *a;
		free(a);
	}
	else
	{
		hashcode = hash(&a->word);

		b = word_ht[hashcode];

		a->next = b;

		word_ht[hashcode] = *a;
	}
}

int cmp_name(const void *a, const void *b)
{
    return strcmp(a, b);
}

char *freadname(void *ptr, int len, FILE* stream)
{
    return fgets(ptr, len, stream);
}