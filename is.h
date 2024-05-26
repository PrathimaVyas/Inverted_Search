#ifndef IS_H
#define IS_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define FAILURE 0
#define SUCCESS 1


typedef struct filename
{
    char *filename;
    struct filename *link;
}filenode;

typedef struct subnode
{
    int wordcount;
    char filename[20];
    struct subnode *link;
}sub_t;

typedef struct mainnode
{
    int filecount;
    char word[20];
    struct mainnode *mlink;
    sub_t *slink;
}main_t;

typedef struct hashtable
{
    int index;
    main_t *link;
}hash_t;

int validate(int argc,char *file,int i,char *argv[]);
int check_duplicate(char *file,char **argv,int argc,int i);
int insert_at_last(char *file,filenode **head);
int print_sll(filenode *head);


int create_database(hash_t *hashtable,filenode **head);
int find_index(char ch);
int store_database(hash_t *hashtable,filenode *temp);
main_t *create_mainnode(hash_t *hashtable,char *word,char *filename,int index);
int compare_files_in_update_cla(filenode *temp,hash_t *hashtable);

int display_HT(hash_t *hashtable,filenode *head);

int search_database(hash_t *arr,char *word);
int save_database(hash_t *arr,char *word);
int update_database(hash_t *arr,char *filename,filenode **head);

int check_duplicate_files(char *filename,filenode **head);
int store_data_in_newlist(char *filename,filenode **head);



#endif
