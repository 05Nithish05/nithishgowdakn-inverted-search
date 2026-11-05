#include "main.h"

/*=============================================================*/
/* Function : display_database                                */
/* Description : Display complete database                    */
/*=============================================================*/

Status display_database(hash_t *hash)
{
    // Loop variable
    int i;

    // Main node pointer
    main_node *mtemp;

    // Sub node pointer
    sub_node *stemp;

    printf("\n");
    {
        const char *title = "INVERTED SEARCH DATABASE";
        printf(BLUE"%*s\n"RESET, (67 + (int)strlen(title)) / 2, title);
    }
    printf("===================================================================\n");
    printf("%-8s %-20s %-12s %-12s %-12s\n",
           "Index", "Word", "File Count", "File Name", "Word Count");
    printf("===================================================================\n");

for (i = 0; i < 27; i++)
{
    if (hash[i].main_link == NULL)
        continue;

    mtemp = hash[i].main_link;

    while (mtemp != NULL)
    {
        stemp = mtemp->sub_link;

        /* Print first row */
        if (stemp != NULL)
        {
            printf("%-8d %-20s %-12d %-12s %-12d\n",
                   i,
                   mtemp->word,
                   mtemp->file_count,
                   stemp->file_name,
                   stemp->word_count);

            stemp = stemp->sub_link;
        }

        /* Print remaining sub nodes */
        while (stemp != NULL)
        {
            printf("%-8s %-20s %-12s %-12s %-12d\n",
                   "",
                   "",
                   "",
                   stemp->file_name,
                   stemp->word_count);

            stemp = stemp->sub_link;
        }

        mtemp = mtemp->main_link;
    }
}

    printf("====================================================================\n");

    // Display completed successfully
    return SUCCESS;
}