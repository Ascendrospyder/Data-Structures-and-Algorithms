#include <stdio.h>
#include <stdlib.h> 

#include "BSTree.h"

struct Node {
  int data; 
  Tree left, right; 
} Node; 

/**
 * @brief Function takes in an item to insert into the root and sets the right and left root to null 
 * 
 * @param it - Type Tree
 * @return Tree - which is a new tree
 */
Tree TreeCreate(Item it)
{
  Tree root;
  if ((root = malloc(sizeof(struct Node))) == NULL)
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

/**
 * @brief - This function inserts a node into a tree at a position 
 * 
 * @param t - tree
 * @param it - item we want to insert into tree t 
 * @return Tree 
 */
Tree TreeInsert(Tree t, Item it)
{
  if (t == NULL) // if the tree hasn't been created go ahead and create it with "it" as the root
  {
    return TreeCreate(it); // make sure you return this as this was causing the bug where it wasn't printing the rest of the elements 
  } else if (it < t->data) { // if the value we want to insert into tree is less than root we want to put it into the left 
    t->left = TreeInsert(t->left, it); // left section = recursive call to the tree, where the new "root" (its not the root but we treat it like that) is going to be NULL and from the first if statement, if it is NULL, go ahead create that item into that pos
  } else if (it > t->data) {
    t->right = TreeInsert(t->right, it); // right section = recursive call to the tree, where the new "root" (its not the root but we treat it like that) is going to be NULL and from the first if statement, if it is NULL, go ahead create that item into that pos
  }
  return t; // this avoids duplicates 
}

/**
 * @brief Prints the tree out based on either inorder, preorder or postorder methods 
 * 
 * @param t - Tree
 * @param depth - levels 
 */
void showTreeRecursive(Tree t, int depth); 
void ShowTree(Tree t)
{
  showTreeRecursive(t, 0); // we need to pass in the initial depth as 0 
}

/**
 * @brief Recursive call to print the whole tree out 
 * 
 * @param t - tree
 * @param depth - level 
 */
void showTreeRecursive(Tree t, int depth)
{
  if (t != NULL)
  {
    for (int i = 0; i < depth; i++)
    {
      printf("   "); 
    }
    printf("%d\n", t->data); // print out the root first  
    showTreeRecursive(t->left, depth + 1); 
    showTreeRecursive(t->right, depth + 1);
  }
}

/**
 * @brief Joins two trees together by finding the smallest element in the second tree and then making that the root and updating the second tree and then 
 * adding that updated tree to the left of the root and adding the first tree to the right of the tree
 * @param t - Tree 
 * @param n - Tree 
 * @return Tree - New tree with both joined together 
 */
Tree TreeJoin(Tree t, Tree n)
{
  if (t == NULL) 
  {
    return n; // if the first tree doesnt have anything then return the second tree
  } else if (n == NULL)
  {
    return t; // if the second tree is empty return the first tree 
  } else {
    Tree current = n; // we create a current var which points to our second tree, from now we will use current to traverse the second tree 
    Tree parent = NULL;  // this will be our parent (root node) for this new tree and we initalise it to NULL 

    while (current->left != NULL) // finds the min element in t2, if the left isn't empty keep moving through the left section of t2
    {
      parent = current; // let the element to the left most section of our tree be the parent as we traverse the lhs and reach null which is the end 
      current = current->left; 
    }
    if (parent != NULL) // moves the min element up to the root 
    {
      parent->left = current->right; // the root node's right will now hold the updated 
      current->right = n; 
    }
    current->left = t; // build the left section of our new tree by linking tree 1 to the left of current which now holds the root 
    return current; 
  }
}

/**
 * @brief This function takes in a tree and an item in the tree to delete
 * 
 * @param t - Tree
 * @param it - Item 
 * @return Tree t 
 */
Tree TreeDelete(Tree t, Item it)
{ 
  if (t != NULL) // if tree is not empty then go ahead with the code 
  {
    if (it < t->data)
    {
      t->left = TreeDelete(t->left, it); // if what we want to delete is in the left side of the tree 
    } else if (it > t->data)
    {
      t->right = TreeDelete(t->right, it); // if what we want to delete is in the right side of the tree
    } else 
    {
      Tree current; // set up a current variable which will hold the new tree 
      if (t == NULL) // if tree is empty 
      {
        current = NULL; // if we want to delete a node with 0 children 
      } else if (t->left == NULL) // if left side of the tree is empty, meaning no more children 
      {
        current = t->right; // if we want to delete a node with 1 child
      } else if (t->right == NULL) // if right side of the tree is empty, meaning no more children 
      {
        current = t->left; // if we want to delete a node with 1 child
      } else {
        current = TreeJoin(t->left, t->right); // if we want to delete a child with 2 children 
      } 
      free(t); // finally free t 
      t = current; // set t to current and return t at the end 
    }
  } 
  return t;
}