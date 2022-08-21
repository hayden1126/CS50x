#import <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node
{
    int i;
    struct node *next;
}
node;

// int main(void)
// {
//     node *n = malloc(sizeof(node));
//     n->i = 1;
//     n->next = NULL;

//     node *list = NULL;
//     list = n;

//     n = malloc(sizeof(node));
//     n->i = 0;
//     n->next = list;
//     list = n;


//     printf("%i\n", list->i);
//     printf("%i\n", list->next->i);
//     free(n->next);
//     free(n);
// }

int main(void)
{
    char *word = malloc(46);
    word = "Testing";
    printf("%c\n", word[0]);
}