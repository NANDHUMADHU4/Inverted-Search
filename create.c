#include<stdio.h>
#include"main.h"
#include<string.h>
#include <ctype.h> 


int create_database(Mlist *hash[], Flist **head, Flist **backupfile)
{
    Flist *ftemp = *head;
    Flist *fprev = NULL;
    Flist *btemp = *backupfile;
    while (btemp != NULL)
    {
	ftemp = *head;
	while (ftemp != NULL)
	{
	    if (strcmp(btemp -> filename , ftemp -> filename) == 0)
	    {
		if (*head == ftemp)
		{
		    *head = ftemp -> filelink;
		    free(ftemp);
		    ftemp = *head;
		    break;
		}
		else
		{
		    fprev -> filelink = ftemp -> filelink;
		    free(ftemp);
		    if (fprev -> filelink == NULL)
		    {
			break;
		    }
		    ftemp = fprev -> filelink;
		}
	    }
	    fprev = ftemp;
	    ftemp = ftemp -> filelink;	   
	}
	btemp = btemp -> filelink;
    }
    if (*head == NULL)
    {
	printf("ERROR : Same file as in backupfile\n");
	return FAILURE;
    }
    Flist *temp = *head;
    FILE *fptr;
    char word[50];
    int ind;
    while (temp != NULL)
    {
	fptr = fopen(temp -> filename, "r");
	fseek(fptr,0,SEEK_SET);
	//scaning each word from the file using fscanf till End Of File
	while (fscanf(fptr, "%s", word) != EOF)
	{
	    //converting each 1st chara of word to upper case
	    if ( (word[0] >= 'A' && word[0] <= 'Z') || (word[0] >='a' && word[0] <= 'z') )
	    {
		ind = toupper(word[0])-65;
	    }
	    else
	    {
		ind = 26;
	    }
	    if (hash[ind] == NULL)
	    {
		hash[ind] = create_mainnode(word, temp);
	    }
	    else
	    {
		Mlist *mtemp = hash[ind];
		Mlist *mprev = NULL;
		while (mtemp != NULL)
		{
		    if (strcmp(mtemp -> word , word) == 0)
		    {
			Slist *stemp = (mtemp -> sublink);
			Slist *sprev = NULL;
			while (stemp != NULL)
			{
			    if (strcmp(temp -> filename , stemp -> filename) == 0)
			    {
				(stemp -> word_count)++;
				break;
			    }
			    sprev = stemp;
			    stemp = stemp -> sublink; 
			}
			if (stemp == NULL)
			{
			    sprev -> sublink = create_subnode(temp);
			    (mtemp -> file_count)++;
			}
			break;
		    }
		    mprev = mtemp;
		    mtemp = mtemp -> mainlink;
		}
		if (mtemp == NULL)
		{
		    mprev -> mainlink = create_mainnode(word,temp);
		}
	    }
	}
	fclose(fptr);
	temp = temp -> filelink;	
    }
    return SUCCESS;

}

Mlist *create_mainnode(char word[],Flist *temp)
{
    Mlist *newmain = malloc(sizeof(Mlist));
    newmain -> file_count = 1;
    strcpy(newmain -> word,word);
    newmain -> mainlink = NULL;
    newmain -> sublink = create_subnode(temp);
    return newmain;

}

Slist *create_subnode(Flist *temp)
{
    Slist *subnew = malloc(sizeof(Slist));
    subnew -> word_count = 1;
    subnew -> sublink = NULL;
    strcpy(subnew -> filename, temp -> filename);
    return subnew;

}

