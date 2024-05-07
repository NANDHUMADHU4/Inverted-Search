
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE -1


typedef struct m_node
{
    char word[50];
    int file_count;
    struct s_node *sublink;
    struct m_node *mainlink;
}Mlist;

typedef struct s_node
{
    int word_count;
    char filename[50];
    struct s_node *sublink;
}Slist;


typedef struct f_node
{
    char filename[50];
    struct f_node *filelink;
}Flist;

int read_and_validate_argv(Flist **head, int argc, char *argv[]);
int create_database(Mlist *hash[], Flist **head, Flist **backupfile);
Mlist *create_mainnode(char word[], Flist *head);
Slist *create_subnode(Flist *head);
int display(Mlist *hash[]);
int search(Mlist *hash[]);
int save (Mlist *hash[]);
int update(Mlist *hash[], Flist **backupfile);
