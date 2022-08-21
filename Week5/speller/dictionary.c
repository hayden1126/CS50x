// Implements a dictionary's functionality

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table up to all combination of words with (first) 6 characters
// basically the total needed to cover all possible combinations with all lengths from 1 - 6 (6 + words will be stored at 6) is:
// (26) + (26 x 27) + (26 x 27^2) + (26 x 27^3) + (26 x 27^4) + (26 x 27^5) =
const unsigned int N = 387420488;

// Hash table
// Each of the group of words sorted by length takes 26, 702, 18954, 511758, 13817466, 373071582 spaces respectively, with total N = 387420488
node *table[N];
// Positions designated for the first of words with char lengths 1, 2, 3, 4, 5, 6 respectively
unsigned int hash_loc[] = {0, 26, 728, 19682, 531440, 14348906}; // e.g. table[0-25] is for all 1 char words, table[26-727] for 2 char words...

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
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
    // TODO: Improve this hash function
    unsigned int index = 0;
    // For each letter, calculate and add to index
    int length = strlen(word);
    for (int i = 0; i < length && i < 6; i++)
    {
        index += (semi_hash(word[i]) * pow(27, N - i - 1));
    }
    // Find the correct position in table according to their designated loc for their number of characters length
    if (length < 7)
    {
        index += hash_loc[length - 1];
    }
    else
    {
        index += hash_loc[5];
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
    while (fscanf(dict, "%s", word) != EOF)
    {
        unsigned int index = hash(word);
        // printf("%i word: %s\n", index, word);
        // count++;
        // Insert word at correct node
        // Check if node is empty
        if (table[index] == NULL)
        {
            new_node = malloc(sizeof(node));
            strcpy(new_node->word, word);
            new_node->next = NULL;
            table[index] = new_node;
        }
        // If node is occupied, insert at the beginning
        else
        {
            new_node = malloc(sizeof(node));
            strcpy(new_node->word, word);
            new_node->next = table[index];
            table[index] = new_node;
        }

    }
    // unsigned int count = 0;
    printf("teststart\n");
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            count++;
            printf("%i %s\n", i, table[i]->word);
            node *nextn = table[i]->next;

            while (nextn != NULL)
            {
                printf("%i %s\n", i, nextn->word);
                nextn = nextn->next;
            }
        }
    }
    printf("testfinish\n");
    printf("%i\n", count);
    fclose(dict);
    free(word);
    return true;
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
