#include<stdio.h>
#include"main.h"
#include<string.h>



int save(Mlist *hash[])
{
    char bfname[50];
    printf("Enter the backupfilename : ");
    scanf("%s", bfname);
    if (strcmp(strstr(bfname, "."), ".txt") == 0)
    {
	FILE *fptr;
	fptr = fopen(bfname, "w");
	for (int ind=0; ind < 27; ind++)
	{
	    if (hash[ind] != NULL)
	    {
		Mlist *mtemp = hash[ind];
		while (mtemp != NULL)
		{
		    fprintf(fptr, "#%d;", ind);
		    fprintf(fptr, "%s;", mtemp -> word);
		    fprintf(fptr, "%d;", mtemp -> file_count);
		    Slist *stemp = mtemp -> sublink;
		    while (stemp != NULL)
		    {
			fprintf(fptr, "%s;", stemp -> filename);
			fprintf(fptr, "%d;", stemp -> word_count);
			stemp = stemp -> sublink;
		    }
		    fprintf(fptr, "#");
		    fprintf(fptr, "\n");
		    mtemp = mtemp -> mainlink;
		}
	    }
	}
    }
    else
    {
	printf("not a .txt file\n");
    }
}


