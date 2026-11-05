#include "main.h"

/* Validate file */

Status validate_file(char *fname)
{
    FILE *fptr;

    // Get the file extension
    char *ext = strrchr(fname,'.');

    // Check whether the file has .txt extension
    if(ext == NULL || strcmp(ext,".txt"))
    {
        printf(RED "%s -> Invalid file extension\n" RESET, fname);
        return FAILURE;
    }

    // Open the file in read mode
    fptr = fopen(fname,"r");

    // Check if the file exists
    if(fptr == NULL)
    {
        printf(RED "%s -> File not found\n" RESET, fname);
        return FAILURE;
    }

    // Move file pointer to the end of the file
    fseek(fptr,0,SEEK_END);

    // Check whether the file is empty
    if(ftell(fptr) == 0)
    {
        printf(RED "%s -> Empty file\n" RESET, fname);
        fclose(fptr);
        return FAILURE;
    }

    // Close the file
    fclose(fptr);

    return SUCCESS;
}

/* Duplicate check */

Status check_duplicate(file_node *head,char *fname)
{
    // Traverse the linked list
    while(head)
    {
        // Compare file names
        if(strcmp(head->file_name,fname)==0)
            return SUCCESS;

        // Move to the next node
        head=head->link;
    }

    return FAILURE;
}

/* Insert file */

Status insert_file(file_node **head,char *fname)
{
    // Allocate memory for a new file node
    file_node *new=malloc(sizeof(file_node));

    // Check memory allocation
    if(new==NULL)
        return FAILURE;

    // Copy file name into the node
    strcpy(new->file_name,fname);

    // Initialize link to NULL
    new->link=NULL;

    // Insert as the first node if list is empty
    if(*head==NULL)
    {
        *head=new;
        return SUCCESS;
    }

    // Traverse to the last node
    file_node *temp=*head;

    while(temp->link)
        temp=temp->link;

    // Link the new node at the end
    temp->link=new;

    return SUCCESS;
}

/* Check if file already exists in the database */
Status is_file_in_database(hash_t *hash, char *fname)
{
    for (int i = 0; i < 27; i++)
    {
        main_node *mtemp = hash[i].main_link;

        while (mtemp != NULL)
        {
            sub_node *stemp = mtemp->sub_link;

            while (stemp != NULL)
            {
                if (strcmp(stemp->file_name, fname) == 0)
                    return SUCCESS;

                stemp = stemp->sub_link;
            }

            mtemp = mtemp->main_link;
        }
    }

    return FAILURE;
}