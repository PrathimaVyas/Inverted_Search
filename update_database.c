#include"is.h"

int update_database(hash_t *arr, char *filename,filenode **head)
{
    filenode *newlist = NULL;
    FILE *fptr = fopen(filename,"r");
    if(fptr != NULL)      //check file is present or not
    {
	char str[40];
	int index;
	int len;
	while(fscanf(fptr,"%s",str) != EOF)
	{
	    len = strlen(str);
	    if(str[0] != '#' || str[len-1] != '#')  
		//check the first and last character it must be '#', if it is not '#' the print error message
	    {
		return FAILURE;
	    }

	    index = atoi(strtok(str+1,";"));
	    //main node creation and linking to the hashtable
	    main_t *mnew = malloc(sizeof(main_t));
	    if(mnew == NULL)
		return FAILURE;
	    strcpy(mnew->word , strtok(NULL,";"));
	    mnew -> filecount = atoi(strtok(NULL,";"));
	    mnew -> mlink = NULL;
	    mnew -> slink = NULL;
	    main_t *mtemp ;
	    sub_t *stemp;

	    if(arr[index].link == NULL) 
		//check hastable link is null or not if it is null update with mainnode link
	    {
		arr[index].link = mnew;
		mtemp = arr[index].link;
	    }
	    else
	    {
		mtemp = arr[index].link;
		while(mtemp->mlink)
		{
		    mtemp = mtemp -> mlink;
		}
		mtemp -> mlink = mnew;
		mtemp = mnew;
	    }

	    //run the loop for filecount times to update multiple number of sublinks
	    for(int i=0;i < mnew -> filecount ; i++)
	    {
		//subnode creation and linking to the hashtable
		sub_t *snew = malloc(sizeof(sub_t));
		if(snew == NULL)
		    return FAILURE;
		strcpy(snew->filename,strtok(NULL, ";"));

		if(check_duplicate_files(snew->filename,&newlist) == SUCCESS)  //check for the duplicate files same as the validation
		{
		    store_data_in_newlist(snew->filename,&newlist);
		}

		snew->wordcount = atoi(strtok(NULL,";"));
		snew->link = NULL;
		if(mtemp->slink == NULL)
		{
		    mtemp -> slink = snew;
		    stemp = snew;
		}
		else
		{
		    stemp = mtemp -> slink;
		    while(stemp->link)
			stemp = stemp -> link; 
		    stemp->link = snew;

		    stemp = stemp -> link; 
		}
	    }
	}

	//print the newlist which is having the filenames which are present in the backup file
	printf("Database is updated with ");
	filenode *temp = newlist;
	while(temp)
	{
	    printf("%s ",temp->filename);  //files present in the backup file
	    temp=temp->link;
	}
	printf("\n");

	return SUCCESS;
    }
    else
    {
	printf("%s is not present\n",filename);
	return FAILURE;
    }
}

int check_duplicate_files(char *filename,filenode **head)
{
    filenode *temp = *head;
    while(temp)
    {
	if(strcmp(temp->filename,filename) == 0)   //compare the filenames in the backup file and command line
	{ 
	    return FAILURE;
	}
	temp = temp->link;
    }
    return SUCCESS;
}

int store_data_in_newlist(char *filename,filenode **head)
{
    filenode *new = malloc(sizeof(filenode));
    if(new == NULL)
	return FAILURE;

    new->filename = filename;
    new->link = NULL;

    if(*head == NULL)
    {
	*head = new;
	return SUCCESS;
    }

    filenode *temp = *head;
    while(temp->link)
    {
	temp = temp->link;
    }
    temp->link = new;
    return SUCCESS;
}




