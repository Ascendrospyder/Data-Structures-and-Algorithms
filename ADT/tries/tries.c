#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

typedef struct Node *Trie; 
typedef char *Key; 

typedef int Item; 

typedef struct Node {
    char onechar; // current char in key 
    Trie child[ALPHABET_SIZE]; // 
    bool finish; // if its finished or not (marks the end of one key but it can have more children)
    Item data; // keeps track of the frequence of the data? not sure tbh 
} Node; 

Trie new_trie(char data)
{
    Trie new = malloc(sizeof(Node));

    // populate the struct 
    new->onechar = data; 
    new->finish = false; 
    new->data = 

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        new->child[i] = NULL; 
    }   
    


}

Trie insert(Trie t, Item it, Key key)
{
    if (t == NULL)
    {
        t = 
    }
}

