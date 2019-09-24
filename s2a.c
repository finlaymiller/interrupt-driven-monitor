#include "s2a.h"

char **strToArray(char *string, const char *delim, int num_tok)
{
	printf("\nSeparating string:\t");
	// tokenize input string
	char *token_array[num_tok];	// initialize array for string pointers
	int i = 0;
	token_array[i] = strtok(string, delim);	// add first pointer to array
	while(token_array[i] != NULL)
		token_array[++i] = strtok(NULL,delim);	// add rest of pointers

	// now we have an array of strings...locally.
	// How do we get it back to the mainline?
	char **tok_ptr = token_array;
	char **string_array = malloc(sizeof(char *) * (num_tok + 1));
	int j = 0;
	while(*tok_ptr)
	{
		string_array[j] = malloc(sizeof(char) * strlen(*tok_ptr));
		strcpy(string_array[j++], *tok_ptr);
		*tok_ptr++;
	}
	
	int k;
	for(k = 0; k < num_tok; k++)
		printf("%s\t", string_array[k]);

	return string_array;
}
