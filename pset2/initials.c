#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

void findInits(char *array1, char *array2, int len);

int main(int argc, char* argv[])
{
	// ensure correct amount of arguments. no arguments.
	if(argc != 1)
	{
		printf("Usage: ./initials\n");
		return 1;
	}

	//initialize variables.
	char *name;
	int size = 6;
	char *initials = malloc(sizeof(char) * size);
	int len;

	//ask for name. loop if null.
	name = GetString();
		

	//store end of string without null term.
	len = strlen(name);

	//call find intials function/
	findInits(name, initials, len);

	//iterate and print array.
	for(int i = 0, j = strlen(initials); i < j; i++)
	{
		initials[i] = toupper(initials[i]);
		printf("%c", initials[i]);
	}
	//print new line
	printf("\n");
}

// function to extract initials.
void findInits(char *array1, char *array2, int len)
{
	// initialize variables
	char init;

	//get first initial.
	init = array1[0];
	strncat(array2, &init, 1);

	for(int i = 0; i < len; i++)
	{
		//get initials after every space.
		if(array1[i] == ' ')
		{
			size_t pos = 1;
			init = array1[i + 1];
			strncat(array2, &init, pos++);
		}
	}
}
