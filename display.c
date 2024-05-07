#include<stdio.h>
#include"main.h"


int display(Mlist *hash[])
{
    for (int ind=0; ind < 27; ind++)
    {
	if (hash[ind] != NULL)
	{
	    Mlist *mtemp = hash[ind];
	    while (mtemp != NULL)
	    {
		printf("[%d]\t%s\t%d", ind, mtemp -> word, mtemp -> file_count);
		Slist *stemp = mtemp -> sublink;
		while (stemp != NULL)
		{
		    printf("\t%s\t%d", stemp -> filename, stemp -> word_count);
		    stemp = stemp -> sublink;
		}
		printf("\n");
		mtemp = mtemp -> mainlink;
	    }
	}
    }
    return SUCCESS;
}
