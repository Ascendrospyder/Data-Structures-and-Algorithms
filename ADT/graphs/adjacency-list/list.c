#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "list.h"

typedef struct Node {
    int data; 
    struct Node *next; 
}Node;
/**
 * @brief - this creates a node 
 * 
 * @param n - int n = data of the node 
 * @return Node* new_node
 */
Node *makeNode (int n)
{
    Node *new = malloc(sizeof(Node)); // allocate some memory for new node 
    assert(new != NULL); // show an error if the condition is false 

    new->data = n; // populate the struct 
    new->next = NULL; 
    return new; // return the new node 
}

/**
 * @brief - inserts a node into the head of the linked list 
 * 
 * @param L - List 
 * @param n - int   
 * @return List 
 */
List insertLL (List L, int n)
{
    if(inLL(L, n)) // if the node is already in the LL return the normal L 
    {
        return L; 
    }
    // add the new_node into the head 
    Node *new_node = makeNode(n); // else create a new node 
    new_node->next = L; // assign the new_nodes next value to 
    return new_node; 
}

/**
 * @brief - deletes a linked list 
 * 
 * @param L 
 * @param n 
 * @return List 
 */
List deleteLL(List L, int n)
{
    if (L == NULL) // if the list doesn't exist return L 
    {
        return L; 
    } else if (L->data == n) // if the data value of the linked list is the same as n
    {
        return L->next; // return the next node of the linked list 
    } else {
        L->next = deleteLL(L->next, n); 
        return L; 
    }
}

/**
 * @brief - checks if a particular data value exists in the linked list 
 * 
 * @param L - List l
 * @param n - int n = data 
 * @return true 
 * @return false 
 */
bool inLL (List L, int n)
{
    if (L == NULL) // if the list is empty return false 
    {
        return false; 
    } else if (L->data == n){ // if the list contains the data return true 
        return true; 
    }
    return inLL(L->next, n); // make a recursive call to check the next element
}

/**
 * @brief - prints the contents of a linked list recursively 
 * 
 * @param L - List l 
 */
void showLL(List L)
{
    if (L == NULL) // if the list is empty print a new line 
    {
        printf("\n"); 
    } else {
        printf("%d ", L->data);  // if not empty then print a new line 
        showLL(L->next); // make a recursive call to print the next element 
    }
}

/**
 * @brief - The following function frees a linked list 
 * 
 * @param L - takes in a list L
 */
void freeLL(List L)
{
    if (L != NULL) // if it isn't empty 
    {
        freeLL(L->next); // free the next element from the head
        free(L); // finally free the head 
    }
}