#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[]) 
{
	//initialize variables.
	string message;

	if (argv[1] == NULL)
	{
		printf("error check key\n");
		return 1;
	}

	//convert and check key.
	int key = atoi(argv[1]);

	if (key < 0) 
	{
		printf("error check key\n");
		return 1;
	}

	if (argc != 2)
	{
		printf("Usage: ./caesar [key]\n");
		return 1;
	} 
	
	//prompt for message.
	message = GetString();

	for (int i = 0, j = strlen(message); i < j; i++) 
	{
		//initialize variables.
 		int c = message[i];

 		if (!isalpha(c))
 		{
 			printf("%c", c);
 		}
 		else
 		{
 			if (islower(c)) 
 			{
 				int e = c + key;
 					if (e > 'z') 
 				{
 					int a = c - 'a';
 					int b = (a + key) % 26;
 					e = b + 'a';
 				} 
 					printf("%c", e);
 			}
 			else if (isupper(c)) 
 			{	
 				int E = c + key;
 				if (E > 'Z')
 				{
 					int A = c - 'A';
 					int B = (A + key) % 26;
 					E = B + 'A';
 				}
 					printf ("%c", E);
 			} 
 		} 
 	}
 	printf("\n");
}

