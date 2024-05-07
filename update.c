#include<stdio.h>
#include<string.h>
#include"main.h"


int update(Mlist *hash[], Flist **backupfile)
{
    int count=0;
    for (int ind =0; ind < 27; ind++)
    {
	if (hash[ind] == NULL)
	{
	    count++;
	}
    }
    if (count == 27)                   //checking all the elements in hash[] is NULL or not
    {
	char backupfname[50];
	printf("Enter the backup filename :");
	scanf("%s", backupfname);
	if (strcmp(strstr(backupfname,"."), ".txt") == 0)
	{
	    FILE *fptr;
	    fptr = fopen(backupfname, "r");
	    if (fptr == NULL)
	    {
		printf("ERROR : Opening backupfile");
		return FAILURE;
	    }
	    char ch1,ch2;
	    fseek(fptr,0,SEEK_SET);
	    fscanf(fptr,"%c",&ch1);
	    fseek(fptr,-2,SEEK_END);
	    fscanf(fptr,"%c",&ch2);
	    fseek(fptr,0,SEEK_SET);
	    if (ch1 == '#' && ch2 == '#')
	    {
		//printf("1st and last chara is #, a backupfile\n");
		char word[50];
		int ind;
		fseek(fptr,0,SEEK_SET);
		while ( fscanf(fptr, "%s", word) == 1)
		{
		    ind = atoi(strtok(word, "#;"));                     //taking the 1st word using strtok and convering this chara to int
		    Mlist *newmain = malloc(sizeof(Mlist));
		    if (newmain == NULL)
		    {
			printf("Memory allocation failure\n");
			return FAILURE;
		    }
		    if (hash [ind] == NULL)
		    {
			hash[ind] = newmain;
		    }
		    else
		    {
			Mlist *mtemp = hash[ind];
			while (mtemp -> mainlink != NULL)
			{
			    mtemp = mtemp -> mainlink;
			}
			mtemp -> mainlink = newmain;
		    }
		    strcpy(newmain -> word,strtok(NULL, "#;"));
		    newmain -> file_count = atoi(strtok(NULL,"#;"));
		    newmain -> mainlink = NULL;
		    newmain -> sublink = NULL;
		    for(int i=0; i < (newmain -> file_count); i++)
		    {
			Slist *newsub = malloc(sizeof(Slist));
			if (newsub == NULL)
			{
			    printf("Memory allocation failure\n");
			    return FAILURE;
			}
			if ( (newmain -> sublink) == NULL)
			{
			    newmain -> sublink = newsub;
			}
			else
			{
			    Slist *stemp = (newmain -> sublink);
			    while (stemp -> sublink != NULL)
			    {
				stemp = stemp -> sublink;
			    }
			    (stemp -> sublink) = newsub;
			}
			strcpy( newsub -> filename, strtok(NULL,"#;"));
			//storing backupfnames in a backupfile list
			Flist *backupfname = malloc(sizeof(Flist));
			Flist *ftemp = *backupfile;
			if (*backupfile == NULL)
			{
			    *backupfile = backupfname;
			}
			else
			{
			    while (ftemp -> filelink != NULL)
			    {
				ftemp = ftemp -> filelink;
			    }
			    ftemp -> filelink = backupfname;
			}
			strcpy(backupfname -> filename,newsub -> filename);
			backupfname -> filelink = NULL;
			newsub -> word_count = atoi(strtok(NULL, "#;"));
			newsub -> sublink = NULL;
		    }
		}
	    }
	    else
	    {
		printf("not a backupfile\n");
		return FAILURE;
	    }
	    fclose(fptr);
	}
	else
	{
	    printf("not a '.txt' file\n");
	    return FAILURE;
	}
    }
    else
    {
	printf("Contents in hash array\n");
	return FAILURE;
    }
    return SUCCESS;
}



