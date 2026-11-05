/*---------------------------------------------------------------------

                    INVERTED SEARCH

-----------------------------------------------------------------------

Name        : Nithish Gowda K N
Batch No    : 26005B
Date        : 09/09/2026

** Description :

The Inverted Search project uses a Hash Table as its primary 
data structure to organize and search words efficiently across 
multiple text files. Every distinct word is stored in a hash table
bucket as a Main Node, while associated Sub Nodes store the 
filenames in which the word occurs along with its frequency count. 
This structure provides quick insertion, indexing, and retrieval of words, 
making the search process efficient even for large collections of text files.

** Supported Operations :

1. Create Database
2. Display Database
3. Search Word
4. Save Database
5. Update Database

** Example Execution :

./a.out f1.txt f2.txt f3.txt f6.txt

** Data Structures Used :

1. Hash Table
2. Singly Linked List (File List)
3. Main Node Linked List
4. Sub Node Linked List
====================================================================*/

#include "main.h"

int main(int argc, char *argv[])
{
    // Head pointer for file linked list
    file_node *head = NULL;

    // Hash table
    hash_t hash[27];

    // Track whether the database has been built or updated
    int db_created = 0;

    // Store user's menu choice
    int choice;

    // Store word to search
    char word[SIZE];

    // Store save/update file name
    char save_file[SIZE];

    /* Initialize Hash Table */

    // Initialize all hash table indices
    for (int i = 0; i < 27; i++)
    {
        hash[i].index = i;
        hash[i].main_link = NULL;
    }

    /* Check command line arguments */

    // Check whether file names are provided
    if (argc < 2)
    {
        printf(RED "ERROR : Pass the file names\n" RESET);
        printf(YELLOW "Usage : ./a.out file1.txt file2.txt ...\n" RESET);
        return FAILURE;
    }

    /* Validate all files */

    // Validate every command-line file
    for (int i = 1; i < argc; i++)
    {
        // Skip invalid files
        if (validate_file(argv[i]) == FAILURE)
            continue;

        // Check duplicate file
        if (check_duplicate(head, argv[i]) == SUCCESS)
        {
            printf(YELLOW "INFO : %s is duplicate\n" RESET, argv[i]);
            continue;
        }

        // Insert valid file into linked list
        if (insert_file(&head, argv[i]) == FAILURE)
        {
            printf(RED "ERROR : Unable to insert %s\n" RESET, argv[i]);
            continue;
        }

        printf(GREEN "INFO : %s added successfully\n" RESET , argv[i]);
    }

    // Check whether any valid file exists
    if (head == NULL)
    {
        printf(RED "ERROR : No valid files found\n" RESET);
        return FAILURE;
    }

    // Display menu continuously
    while (1)
    {
        printf("\n=====================================\n");
        printf(BLUE "      INVERTED SEARCH \n" RESET);
        printf("=====================================\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Search Word\n");
        printf("4. Save Database\n");
        printf("5. Update Database\n");
        printf("6. Exit\n");
        printf("=====================================\n");
        printf("Enter your choice : ");

        // Read user choice
        {
            char input[SIZE];
            char extra;
            if (fgets(input, sizeof(input), stdin) == NULL)
            {
                printf(RED "ERROR : Invalid Choice\n" RESET);
                continue;
            }

            if (sscanf(input, " %d %c", &choice, &extra) != 1)
            {
                printf(RED "ERROR : Invalid Choice\n" RESET );
                continue;
            }
        }

        // Perform selected operation
        switch (choice)
        {
            case 1:
            {
                if (db_created)
                {
                    printf(YELLOW "INFO : Database already created\n" RESET);
                    break;
                }

                if (create_database(head, hash) == SUCCESS)
                {
                    printf(GREEN "INFO : Database created successfully\n" RESET);
                    db_created = 1;
                }
                else
                {
                    printf(RED "ERROR : Failed to create database\n" RESET);
                }

                break;
            }

            case 2:
            {
                // Display the database
                if (display_database(hash) == FAILURE)
                    printf(BLUE "ERROR : Database is empty\n" RESET);

                break;
            }

            case 3:
            {
                // Read word to search
                printf("Enter the word to search : ");
                {
                    char input[SIZE];
                    char extra;
                    if (fgets(input, sizeof(input), stdin) == NULL || sscanf(input, " %49s %c", word, &extra) != 1)
                    {
                        printf(RED "ERROR : Invalid input\n" RESET);
                        break;
                    }
                }

                // Search the word
                if (search_database(hash, word) == FAILURE)
                    printf(BLUE "INFO : Word not found\n" RESET);

                break;
            }

            case 4:
            {
                // Read save file name
                printf("Enter save file name : ");
                {
                    char input[SIZE];
                    char extra;
                    if (fgets(input, sizeof(input), stdin) == NULL || sscanf(input, " %49s %c", save_file, &extra) != 1)
                    {
                        printf(RED "ERROR : Invalid input\n" RESET);
                        break;
                    }
                }

                // Save database
                if (save_database(hash, save_file) == SUCCESS)
                    printf(GREEN "INFO : Database saved successfully\n" RESET);
                else
                    printf(RED "ERROR : Failed to save database\n" RESET);

                break;
            }

            case 5:
            {
                // Read backup file name
                printf("Enter backup file name : ");
                {
                    char input[SIZE];
                    char extra;
                    if (fgets(input, sizeof(input), stdin) == NULL || sscanf(input, " %49s %c", save_file, &extra) != 1)
                    {
                        printf(RED "ERROR : Invalid input\n" RESET);
                        break;
                    }
                }

                // Update database from backup and process new files
                if (update_database(hash, save_file, head) == SUCCESS)
                {
                    printf(GREEN "INFO : Database updated successfully\n" RESET);
                    db_created = 1;
                }
                else
                {
                    printf(RED "ERROR : Failed to update database\n" RESET);
                }

                break;
            }

            case 6:
            {
                // Exit the program
                printf("Exiting...\n");
                return SUCCESS;
            }

            default:
            {
                // Invalid menu option
                printf(RED "ERROR : Invalid Choice\n" RESET);
            }
        }
    }

    return SUCCESS;
}