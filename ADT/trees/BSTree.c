#include <stdio.h>
#include <stdlib.h> 

#include "BSTree.h"

typedef struct Node {
  int data; 
  Tree left, right; 
} Node; 

Tree TreeCreate(Item it)
{
  Tree root;
  if ((root = = malloc(sizeof(struct Node))) == NULL)
  {
    fprintf(stderr, "Error, malloc failed\n"); 
    exit(EXIT_FAILURE); 
  } 
  root->data = it; // set the root 
  root->left = NULL; // set left and right nodes to NULL because we only want the root first 
  root->right = NULL; 

  return root; 
}

void TreeFree(Tree t) 
{

}

Tree TreeInsert(Tree t, Item it)
{
  return NULL; 
}

void ShowTree(Tree t)
{

}