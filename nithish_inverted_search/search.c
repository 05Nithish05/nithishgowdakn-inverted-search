#include "main.h"

/*------------------------------------------------------------*/
/* Function : search_database                                 */
/* Description : Search a word in the database                */
/*------------------------------------------------------------*/

Status search_database(hash_t *hash, char *word)
{
    // Flag to check whether database is empty
    int flag = 0;

    // Check if any hash table index contains data
    for (int i = 0; i < 27; i++)
    {
        if (hash[i].main_link != NULL)
        {
            flag = 1;
            break;
        }
    }

    // Return if database is empty
    if (flag == 0)
    {
        printf(YELLOW "INFO : Database is empty. Please create or update the database first.\n" RESET);
        return FAILURE;
    }

    // Hash index
    int index;

    // Main node pointer
    main_node *mtemp;

    // Sub node pointer
    sub_node *stemp;

    /* Calculate hash index */

    // Calculate index based on first character
    if (isalpha(word[0]))
        index = tolower(word[0]) - 'a';
    else
        index = 26;

    /* Check hash table empty */

    // Check whether the calculated index is empty
    if (hash[index].main_link == NULL)
    {
        printf(RED "\nWord \"%s\" not found\n" RESET, word);
        return FAILURE;
    }

    // Point to the first main node
    mtemp = hash[index].main_link;

    /* Search main node */

    // Traverse main node list
    while (mtemp != NULL)
    {
        // Compare the word
        if (strcmp(mtemp->word, word) == 0)
        {
            {
                const char *title = "INVERTED SEARCH DATABASE";
                printf(BLUE"%*s\n"RESET, (67 + (int)strlen(title)) / 2, title);
            }
            printf("===================================================================\n");
            printf("%-8s %-20s %-12s %-12s %-12s\n",
                   "Index", "Word", "File Count", "File Name", "Word Count");
            printf("===================================================================\n");

            // Point to first sub node
            stemp = mtemp->sub_link;

            // Print first row
            if (stemp != NULL)
            {
                printf("%-8d %-20s %-12d %-12s %-12d\n",
                       index,
                       mtemp->word,
                       mtemp->file_count,
                       stemp->file_name,
                       stemp->word_count);

                stemp = stemp->sub_link;
            }

            // Print remaining sub nodes
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

            printf("====================================================================\n");
            return SUCCESS;
        }

        // Move to next main node
        mtemp = mtemp->main_link;
    }

    // Word not found
    printf(RED "\nWord \"%s\" not found\n" RESET, word);

    return FAILURE;
}