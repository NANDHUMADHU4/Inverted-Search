#include<stdio.h>
#include <ctype.h>
#include"main.h"
#include<string.h>




int search (Mlist *hash[])
{
    int ind;
    char search_word[50];
    int filenum=0;
    printf("Enter the word you want to search: ");
    scanf("%s", search_word);
    ind = toupper(search_word[0])-65;
    Mlist *mtemp = hash[ind];
    while (mtemp != NULL)
    {
	if (strcmp( mtemp -> word,search_word) == 0)
	{
	    printf("Word %s is present in %d file(s)\n", search_word, mtemp ->file_count);
	    Slist *stemp = mtemp -> sublink;
	    while (stemp != NULL)
	    {
		printf("%s -> %d\n", stemp -> filename, stemp -> word_count);
		stemp = stemp -> sublink;
	    }
	    break;
	}
	mtemp = mtemp -> mainlink;
    }
    if (mtemp == NULL)
    {
	printf("DATA NOT FOUND");
    }
    return SUCCESS;

}

