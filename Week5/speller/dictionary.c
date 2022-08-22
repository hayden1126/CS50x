// Implements a dictionary's functionality

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table up to all combination of words with (first) 4 characters
// basically the total nodes needed to cover all possible combinations with all lengths from 1 - 4 (4+ length words will linked listed at 4) is:
// (26) + (26 x 27) + (26 x 27^2) + (26 x 27^3) = 531440
const unsigned int N = 531440;
const int NO_OF_CHAR = 4; // Number of characters that the table can accomodate (as in all combinations with the 1st 6 characters)

// Hash table
// Each of the group of words sorted by length takes 26, 702, 18954, 511758 spaces/nodes respectively, with total N = 531440
node *table[N];
unsigned int word_count = 0; // number of words in dictionary
// Positions designated for the first word of words with character lengths 1, 2, 3, 4 respectively
unsigned int hash_loc[] = {0, 26, 728, 19682}; // e.g. table[0-25] is for all 1 char words, table[26-727] for 2 char words...

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int length = strlen(word);
    node *current_node = table[hash(word)];
    // While current_node is not empty
    while (current_node != NULL)
    {
        // If the words are the same (regardless of capitalization as implemented in strcasecmp())
        if (strcasecmp(current_node->word, word) == 0)
        {
            return true;
        }
        // If node does not have word, then go on to next node
        current_node = current_node->next;
    }
    // If whole linked list cannot find the word, then it is misspelled, return false
    return false;
}

int semi_hash(char letter)
{
    // If character is an apostrophe/non alphabet
    if (isalpha(letter) == 0)
    {
        return 26;
    }
    // If is an alphabet
    return toupper(letter) - 'A';
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    // TODO
    unsigned int index = 0;

    int length = strlen(word);
    // For each letter
    for (int i = 0; i < length && i < NO_OF_CHAR; i++)
    {
        // Calculate and add to index
        index += (semi_hash(word[i]) * pow(27, NO_OF_CHAR - 1 - i));
    }
    // index right now is only in the correct position within a table of nodes with same length, so:
    // Find the correct position in table according to their designated loc for their number of characters length
    // i.e. add the hash_loc to the index

    // If word is 4 or shorter characters
    if (length <= NO_OF_CHAR)
    {
        index += hash_loc[length - 1];
    }
    // else just categorize them in the same node with 4 characters
    else
    {
        index += hash_loc[NO_OF_CHAR - 1];
    }
    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO Create string variable to store word
    char *word = malloc(LENGTH + 1);
    node *new_node;
    unsigned int count = 0;
    // Scan the file for each word until end of file, put the string/word in the variable word
    FILE *dict = fopen(dictionary, "r");
    // If scanning first word returns EOF --> there is no word in dictionary --> free memory and return false
    if (fscanf(dict, "%s", word) == EOF)
    {
        fclose(dict);
        free(word);
        return false;
    }
    // If dictionary is valid
    do
    {
        // Hash the word then insert it in correct node
        unsigned int index = hash(word);
        word_count++; // This is for the size function later

        // Check if correct node is empty
        // If empty then put that word in that node
        if (table[index] == NULL)
        {
            new_node = malloc(sizeof(node));
            strcpy(new_node->word, word);
            new_node->next = NULL;
            table[index] = new_node;
        }
        // If node is occupied, insert new node at the beginning
        else
        {
            new_node = malloc(sizeof(node));
            strcpy(new_node->word, word);
            new_node->next = table[index];
            table[index] = new_node;
        }
    }
    while (fscanf(dict, "%s", word) != EOF); // do...while loop: so scans words until the end of the file

    // Close file and free memory only used in/for this function (nodes freed later in unload function)
    fclose(dict);
    free(word);
    // Successfully hashed word, loaded dictionary and freed memory, return true
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // word_count is a global which was calculated in the load function already
    return word_count;

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *current_node = NULL;
    node *temp = NULL;
    // For remaining nodes
    for (int i = 0; i < N; i++)
    {
        current_node = table[i];
        // While current_node is not empty
        while (current_node != NULL)
        {
            temp = current_node->next;
            free(current_node);
            current_node = temp;
        }
    }
    return true;
}