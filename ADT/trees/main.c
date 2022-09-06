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
  ShowTree(t); 
  
  return 0; 
}