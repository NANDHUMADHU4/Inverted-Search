#include<stdio.h>
#include"main.h"
#include<string.h>

/*
Name : Nandhu Madhu
Date :
Description :
Sample Input :
Sample Output :
 */ 


int read_and_validate_argv(Flist **head, int argc, char *argv[])
{
    if (argc == 1)
    {
	printf("No arguments passed\n");
	return FAILURE;
    }
    FILE *fptr;
    for (int i=1; i<argc; i++)
    {
	if ( (strstr(argv[i], ".")) != NULL )
	{
	    if (strcmp(strstr(argv[i], "."), ".txt") == 0 )
	    {
		fptr = fopen(argv[i], "r");
		if (fptr != NULL)
		{
		    fseek(fptr,0,SEEK_END);
		    if (ftell(fptr) > 0)
		    {
			if (*head == NULL)
			{
			    Flist *nfilename = malloc(sizeof(Flist));
			    strcpy(nfilename -> filename,argv[i]);
			    nfilename -> filelink = NULL;
			    *head = nfilename;
			}
			else
			{
			    Flist *temp = *head, *prev = NULL;

			    while(temp != NULL)
			    {
				//checking for duplicates
				if (strcmp(temp -> filename ,argv[i]))
				{
				    prev = temp;
				    temp = temp -> filelink;
				}
				else
				{
				    break;
				}
			    }
			    //creating node when no duplicates are found
			    if (temp == NULL)
			    {
				Flist *nfilename = malloc(sizeof(Flist));
				strcpy(nfilename -> filename, argv[i]);
				prev -> filelink = nfilename;
				nfilename -> filelink = NULL;
			    }
			}
		    }
		    else
		    {
			printf("ERROR : File(s) Empty\n");
		    }
		}
		else
		{
		    printf("ERROR : In Opening file(s)\n");
		}
		fclose(fptr);
	    }
	    else
	    {
		printf("ERROR : Not '.txt' file(s) type\n");
	    }
	}
	else
	{
	    printf("ERROR : Not required file(s)\n");
	}
    }
    if (*head != NULL)
    {
	return SUCCESS;
    }
    else
    {
	return FAILURE;
    }

}






int main(int argc, char *argv[])
{

    Flist *head = NULL; 
    Mlist *hash[27] = {NULL};
    Flist *backupfile = NULL;
    if (read_and_validate_argv(&head,argc,argv) == SUCCESS)
    {
	printf("read and validate successful\n");
	int option;
	char condition = 'y';
	while (condition == 'y')
	{
	    printf("Select your choice among following options:\n1. Creat DATABASE\n2. Display Database\n3. Save DATABASE\n4. Search\n5. Update Database\n");
	    printf("Enter your choice\n");
	    scanf("%d", &option);
	    switch (option)
	    {
		case 1:
		    {
			if (create_database(hash,&head,&backupfile) == SUCCESS)
			{
			    printf("INFO: Creating database successfull\n");
			}
			else
			{
			    printf("ERROR in creating database\n");
			}
			break;
		    }
		case 2:
		    {
			if (display(hash) == SUCCESS)
			{
			    printf("INFO: Displaying contents successful\n");
			}
			else
			{
			    printf("ERROR: Displaying contents\n");
			}
			break;
		    }
		case 3:
		    {
			if (save(hash) == SUCCESS)
			{
			    printf("INFO: Saving to a backupfile successful\n");
			}
			else
			{
			    printf("ERROR : Saving to backupfile\n");
			}
			break;
		    }
		case 4:
		    {
			if (search(hash) == SUCCESS)
			{
			    printf("INFO: Searching successful\n");
			}
			else
			{
			    printf("ERROR : Searching failure\n");
			}
			break;
		    }
		case 5:
		    {
			if (update(hash,&backupfile) == SUCCESS)
			{
			    printf("INFO: Updating database successful\n");
			}
			else
			{
			    printf("ERROR : Update database\n");
			}
			break;
		    }
		default:
		    {
			printf("Invalid Option\n");
		    }
	    }
	    printf("Enter y to continue and n to exit\n");
	    scanf(" %c", &condition);
	}
    }
    return 0;
}

