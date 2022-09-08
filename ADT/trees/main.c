#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

int main (int argc, char *argv[])
{
  Tree t = TreeCreate(4);                             
  t = TreeInsert(t, 2);
  t = TreeInsert(t, 6);
  t = TreeInsert(t, 5);
  t = TreeInsert(t, 1);
  t = TreeInsert(t, 7);
  t = TreeInsert(t, 3);

  // Tree s = TreeCreate(6); 
  // printf("Printing before new root:\n"); 
  // ShowTree(s); 

  Tree n = TreeCreate(26);
  n = TreeInsert(n, 24); 
  n = TreeInsert(n, 27); 
  n = TreeInsert(n, 29); 
  n = TreeInsert(n, 22); 
  n = TreeInsert(n, 25); 

  Tree new_root = InsertAtRoot(n, 8); 
  printf("Printing after new root:\n"); 
  ShowTree(new_root); 

  // Tree joined = TreeJoin(t, n); 
  // printf("Joined Tree:\n");
  // ShowTree(joined); 
  // printf("\n\n\nDeleted Tree:\n"); 
  // Tree new_tree = TreeDelete(joined, 4); 
  // ShowTree(new_tree);
  // // FreeTree(new_tree);
  // // printf("\n\n\nFreed Tree:\n");  
  // Tree new = TreeRotateRight(t);
  // printf("\n\n\nNew rotated tree right:\n"); 
  // ShowTree(new);  
  return 0; 
}