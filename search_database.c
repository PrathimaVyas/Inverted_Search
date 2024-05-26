#include"is.h"

int search_database(hash_t *arr, char *word)
{
    hash_t *temp = &arr[find_index(word[0])];
    //it will find the index and that index address should be stored in temp

    main_t *mtemp = temp->link;   //maintemp is temp to the link part
    while (mtemp != NULL)  //if it is not equal to null means check the words same or not
    {
	if (strcmp(mtemp->word, word) == 0)
	{
	    sub_t *stemp = mtemp->slink;  
	    //if the words same means search in the subnode  and run it till stempp reach to null
	    while (stemp != NULL)
	    {
		printf("%s found %d times in %s.\n", mtemp->word, stemp->wordcount, stemp->filename);
		stemp = stemp->link;
	    }
	    return SUCCESS;
	}
	mtemp = mtemp->mlink;
    }
    return FAILURE;
}
