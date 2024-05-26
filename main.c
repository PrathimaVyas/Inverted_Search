#include "is.h"

int updated;
char backup[30];
int main(int argc,char **argv)
{
    static filenode *head = NULL,*newfile=NULL;
    int i,ret;
    int flag=0,choice;
    if(argc == 1)
    {
	printf("INFO: There is no files to validate and create the database\n");
	return FAILURE;
    }
    for(i = 1;i<argc;i++)
    {
	if(validate(argc,argv[i],i,argv) == SUCCESS)       //validate the command line arguments
	{
	    insert_at_last(argv[i],&head);      //then create a single linked list 
	}
    }
    print_sll(head);      //print the single linked list 
    hash_t arr[28];              
    for(i = 0 ; i < 28 ; i++)   //create one empty hashtable
    {
	arr[i].index = i;
	arr[i].link = NULL;
    }

    printf("\n1. Create Database\n2. Display Database\n3. Search Database\n4. Save Database\n5. Update Database\n6. Exit\n");
    while(1)
    {
	printf("\nEnter the choice : "); 
	scanf("%d",&choice);
	switch(choice)
	{
	    case 1:

		if(flag == 0)
		{
		    if(create_database(arr,&head) == SUCCESS)
		    {
			flag = 1;
			printf("\n");
		    }
		    else
		    {
			printf("INFO : Failed to create Database\n");
		    }
		}
		else
		{
		    printf("INFO: Database  already created\n");

		}
		break;
	    case 2:
		if(head == NULL)
		{
		    printf("INFO : The DATABASE IS EMPTY\n");
		    break;
		}
		display_HT(arr,head);
		break;
	    case 3:
		char word[20];
		printf("Enter the word to search : ");
		scanf("%s",word);
		if(search_database(arr,word) == SUCCESS);
		else
		    printf("%s not found in the database\n",word);
		break;
	    case 4:
		char filename[20];
		printf("Enter the filename to store the output : ");
		scanf("%s",filename);
		if(strstr(filename,".txt") != NULL)
		{
		    save_database(arr,filename);
		    printf("Database is stored in %s \n",filename);
		}
		else
		    printf("%s extension must be .txt\n",filename);
		break;
	    case 5:
		int ret;
		if(flag == 1)
		{
		    printf("INFO : We cann't update the database because database created previously\n");
		    break;
		}
		if(updated == 0 )
		{
		    getchar();
		    printf("Enter the file to update : ");
		    scanf("%s",backup);
		    if(strstr(backup,".txt") !=NULL)
		    {

			if(update_database(arr,backup,&head) == SUCCESS)
			    updated = 1;
			else
			    printf("database is not updated\n");
		    }
		    else
			printf("%s should have .txt\n",backup);
		}
		break;
	    case 6:
		return SUCCESS;
	    default :
		printf("Choose option from 1 to 6 \n");
		break;
	}
    }

}


int validate(int argc,char *file,int i,char *argv[])
{
    FILE *fptr;
    if(strstr(file,".txt") != NULL)      //to check whether the file is txt file or not       
    {
	if((fptr = fopen(file,"r")) != NULL)               //if it is txt file then check whether the file is present or not
	{
	    fseek(fptr,0,SEEK_END);
	    if( ftell(fptr) > 0)         //if the file is present then check it is empty file or not
	    {
		if(check_duplicate(file,argv,argc,i) == SUCCESS);   //if the file is not empty then check for the duplicate file if duplicate file not found then insert the filename at the last of the node
		else
		{
		    printf("%s is already exist\n",argv[i]);
		    return FAILURE;
		}
	    }
	    else
	    {
		printf("%s is a empty file\n",argv[i]);
		return FAILURE;
	    }
	}
	else
	{
	    printf("%s not exist\n",argv[i]);
	    return FAILURE;
	}
    }
    else
    {
	printf("%s extension is not valid\n",argv[i]);
	return FAILURE;
    }

    return SUCCESS;
}

int check_duplicate(char *file,char **argv,int argc,int i)   //check for the duplicate files in the command line arguments 
{
    int count=0;
    for(;i<argc;i++)
    {
	if(strcmp(file,argv[i]) == 0)
	    count++;
	if(count > 1)
	{
	    return FAILURE;
	}
    }
    return SUCCESS;
}

int insert_at_last(char *file,filenode **head)        //create a linked list
{
    filenode *new = malloc(sizeof(filenode));
    if(new == NULL)
    {
	printf("Memory allocation failure\n");
	return FAILURE;
    }

    new -> filename = file;
    new -> link = NULL;
    if(*head == NULL)
    {
	*head = new;
	return SUCCESS;
    }

    filenode *temp = *head;

    while(temp->link != NULL)         //one node data will be constant
    {
	temp = temp->link;
    }
    temp->link = new;
    return SUCCESS;
}


int print_sll(filenode *head)
{                                    //print the linked list
    printf("\n");
    filenode *temp = head;
    while(temp!=NULL)
    {
	printf("%s->",temp->filename);
	temp = temp->link;
    }
    printf("NULL\n");
}

