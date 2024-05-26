#include"is.h"
#include<ctype.h>

extern char backup[30];
extern int updated;
int create_database(hash_t *hashtable,filenode **head)
{
    filenode *temp = *head;
    if(temp == NULL)
	return FAILURE;
    printf("Database created for files : ");

    while(temp != NULL)     //traverse the no.of files in the cla times
    {
	if(updated == 0)
	{
	    store_database(hashtable,temp);
	}
	else
	{
	    compare_files_in_update_cla(temp,hashtable);
	}
	temp = temp->link;   //traverse till the end of the filenames in the linked list
    }
    return SUCCESS;
}

int find_index(char ch)   //to find the index
{
    if(isalpha(ch))
	return (tolower(ch) -  97);
    else if(isdigit(ch))
	return 27;
    else
	return 26;
}


int store_database(hash_t *hashtable, filenode *temp)
{
    int index;
    char word[20];
    FILE *fptr;
    fptr = fopen(temp->filename,"r");  //first take the first filename
    if(fptr == NULL)
	return FAILURE;

    while(fscanf(fptr,"%s",word) != EOF)  //next take each word in that file
    {
	index = find_index(word[0]);
	//find the index to link the hashtable
	if(hashtable[index].link == NULL)
	{
	    //hashtable link is null means link will be updated with the mainnode 
	    hashtable[index].link = create_mainnode(hashtable,word,temp->filename,index);
	    //finally update the hashtable link with new mainnode
	}
	else 
	{
	    main_t *mtemp = hashtable[index].link;    
	    //if hasahtable link is not null then take one temp and prev variable for mainnode 
	    main_t *mprev = NULL;

	    int wsflag=1,sflag=1;
	    while(mtemp != NULL)
	    {
		if(strcmp(mtemp->word,word) == 0) 
		{
		    //if words are same then compare the file names is same or not
		    wsflag = 0;
		    sub_t *stemp = mtemp->slink;
		    sub_t *sprev = NULL;
		    while(stemp != NULL)
		    {
			if(strcmp(stemp->filename,temp->filename) == 0) 
			{
			    //if the files are same then increment the wordcount
			    sflag = 0;
			    (stemp->wordcount)++;
			    break;
			}
			sprev = stemp;
			stemp = stemp -> link;
		    }
		    //if(stemp == NULL) 
		    if(sflag)
		    {
			//if words are same but filenames are different then create a new subnode  
			sub_t *new = malloc(sizeof(sub_t));
			if(new == NULL)
			{
			    printf("MEMORY ALLOCATION FAILURE\n");
			    return FAILURE;
			}
			new -> wordcount = 1;
			strcpy(new -> filename,temp->filename);
			new -> link = NULL;
			(mtemp -> filecount)++;
			sprev -> link = new;
		    }
		}
		mprev = mtemp;   
	   	//traverse mprev and mtemp variables
		mtemp = mtemp->mlink;
	    }
	    //if temp of mainnode is null then create mainnode and subnode
	    if(wsflag)
	    {

		mprev -> mlink = create_mainnode(hashtable,word,temp->filename,index);
	    }
	}
    }
    printf("%s ",temp->filename);
}



main_t *create_mainnode(hash_t *hashtable,char *word,char *filename,int index)
    //to create the main and subnodes in this function and return the mainnode address
{
    main_t *mnew = malloc(sizeof(main_t));
    if(mnew == NULL)	
    {
	printf("Memory allocation failure\n");
	return FAILURE;
    }

    sub_t *snew = malloc(sizeof(sub_t));
    if(snew == NULL)	
    {
	printf("Memory allocation failure\n");
	return FAILURE;
    }
    strcpy(mnew->word,word);
    mnew -> filecount = 1;
    mnew -> mlink = NULL;    
    mnew -> slink = snew;
    snew -> wordcount = 1;
    strcpy(snew->filename,filename); 
    snew->link = NULL;

    return mnew;
}


int compare_files_in_update_cla(filenode *temp,hash_t *hashtable)
{
    FILE *fptr = fopen(backup,"r");    //open the backup file by which we updated database
    if(fptr == NULL)
	return FAILURE;

    char str[30];
    int file_exist = 0;

    while(fscanf(fptr,"%s",str) != EOF)
    {   //here we just need the filenames in the backup files so skip index and word 
	strtok(str,";");  //skip the # and index 
	strtok(NULL,";"); //skip the word
	int files = atoi(strtok(NULL,";")); //store the number of files in a variable files
	char *file;

	for(int i=0;i<files;i++)
	{
	    file = strtok(NULL,";");
	    strtok(NULL,";");  //skip the word count
	    if(strcmp(temp->filename,file) == 0)
	    {
		file_exist = 1;              
		continue;
	    }
	}
    }
    if(file_exist == 0 )
    {
	store_database(hashtable,temp);      //store the data to the database 
	file_exist= 0;

    }
}
