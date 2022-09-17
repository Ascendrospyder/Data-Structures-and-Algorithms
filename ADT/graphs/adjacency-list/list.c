#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int v; 
    struct Node *next; 
}

Node *makeNode (int n)
{
    Node *new = malloc(sizeof(Node)); 
    assert(new != NULL); 

    new->v = n;     
    new->next = NULL; 
    return new; 
}

List insertLL (List L, int n)
{
    if(inLL(L, n))
    {
        return L; 
    }

    Node *new_node = makeNode(n); 
    new_node->next = L; 
    return new_node; 
}

List deleteLL(List L, int n)
{
    if (L == NULL)
    {
        return L; 
    } else if (L->v == n)
    {
        return L->next; 
    } else {
        L->next = deleteLL(L->next, n);
        return L; 
    }
}

bool inLL (List L, int n)
{
    if (L == NULL)
    {
        return false; 
    } else if (L->v == n){
        return true; 
    }

    return inLL(L->next, n); 
}

void showLL(List L)
{
    if (L == NULL)
    {
        printf("\n"); 
    } else {
        printf("%d ", L->v); 
        showLL(L->next); 
    }
}

void freeLL(List L)
{
    if (L != NULL)
    {
        freeLL(L->next); 
        free(L); 
    }
}