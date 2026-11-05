#ifndef MAIN_H
#define MAIN_H

#define RESET       "\033[0m"
#define BOLD        "\033[1m"

#define RED         "\033[1;31m"
#define GREEN       "\033[1;32m"
#define YELLOW      "\033[1;33m"
#define BLUE        "\033[1;34m"

// Standard input/output functions
#include <stdio.h>

// Memory allocation functions
#include <stdlib.h>

// String handling functions
#include <string.h>

// Character handling functions
#include <ctype.h>

// Maximum size for words and file names
#define SIZE 50

// Status values returned by functions
typedef enum
{
    FAILURE,
    SUCCESS
} Status;

/* File Linked List */

// Stores input file names
typedef struct file_node
{
    char file_name[SIZE];      // File name
    struct file_node *link;    // Pointer to next file
} file_node;

/* Sub Node */

// Stores file information for each word
typedef struct sub_node
{
    char file_name[SIZE];      // File name
    int word_count;            // Number of occurrences
    struct sub_node *sub_link; // Pointer to next sub node
} sub_node;

/* Main Node */

// Stores each unique word
typedef struct main_node
{
    char word[SIZE];              // Word
    int file_count;               // Number of files containing the word
    struct sub_node *sub_link;    // Pointer to first sub node
    struct main_node *main_link;  // Pointer to next main node
} main_node;

/* Hash Table */

// Hash table entry
typedef struct hash
{
    int index;                    // Hash index
    struct main_node *main_link;  // Pointer to first main node
} hash_t;

/* Validation */

// Validate input file
Status validate_file(char *);

// Check duplicate file
Status check_duplicate(file_node *, char *);

// Insert file into linked list
Status insert_file(file_node **, char *);

// Check if a file already exists in the database
Status is_file_in_database(hash_t *, char *);

/* Database */

// Create inverted search database
Status create_database(file_node *, hash_t *);

// Display complete database
Status display_database(hash_t *hash);

// Search a word in the database
Status search_database(hash_t *hash, char *word);

// Save database into a file
Status save_database(hash_t *hash, char *filename);

// Update database from backup file and process new files
Status update_database(hash_t *hash, char *filename, file_node *head);

#endif