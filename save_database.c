#include"is.h"

int save_database(hash_t *arr, char *filename)
{
    FILE *fptr;
    fptr = fopen(filename,"w");    //if the file is present content in that file will be deleted 
    int i;
    for(i = 0 ;i <28 ;i++)   //run the loop for 28 times for characters,numbers and special symbols
    {
	if(arr[i].link != NULL)  //if hashtable link is not null means fo to the mainnode and then subnode by using fprintf we can store the data into the given file
	{
	    main_t *mtemp = arr[i].link;
	    while(mtemp!= NULL)
	    {
		fprintf(fptr,"#%d;",i);
		fprintf(fptr,"%s;%d;",mtemp->word,mtemp->filecount);
		sub_t *stemp = mtemp->slink;
		while(stemp != NULL)
		{
		    fprintf(fptr,"%s;%d;",stemp->filename,stemp->wordcount);
		    stemp = stemp->link;
		}
		fprintf(fptr,"#\n");
		mtemp = mtemp->mlink;
	    }

	}
    }

} 

