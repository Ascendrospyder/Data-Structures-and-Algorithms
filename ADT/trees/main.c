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

  Tree n = TreeCreate(26);
  n = TreeInsert(n, 24); 
  n = TreeInsert(n, 27); 
  n = TreeInsert(n, 29); 
  n = TreeInsert(n, 22); 
  n = TreeInsert(n, 24); 

  Tree joined = TreeJoin(t, n); 
  ShowTree(joined); 
  return 0; 
}