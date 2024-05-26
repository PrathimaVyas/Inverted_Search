#include"is.h"

int display_HT(hash_t *hashtable,filenode *head)
{
    int i;
    sub_t *stemp = NULL;
    main_t *mtemp = NULL;
    printf("Index\tWord\tFilecount\tFilename\tWordcount\n\n");
    for(i = 0 ; i < 28 ;i++) 
      	//run the loop for 28 times for all 26 alphabets , digits and special characters
    {
	if(hashtable[i].link != NULL)  
	    //hashtable link is not null means it will enter the statements in the condition
	{
	    mtemp = hashtable[i].link;    //store it in mtemp and traverse the subnodes
	    while(mtemp != NULL)
	    {
		printf("%d\t%s\t%d\t\t",i,mtemp->word,mtemp->filecount); 
	       	//printing the mainnode and corresponding subnodes
		stemp = mtemp->slink;
		while(stemp != NULL)
		{
		    printf("%s\t%d\t\t",stemp -> filename , stemp -> wordcount);
		    stemp = stemp -> link;
		}
		mtemp = mtemp->mlink;
		printf("\n");
	    }
	}
    }
    return SUCCESS;
}



