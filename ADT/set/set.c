#include "set.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_ELEMS 10000

struct SetRep {
  int elems[MAX_ELEMS]; 
  int nelems; 
}; 

Set SetCreate() {
  Set s;
  if ((s = malloc(sizeof(struct SetRep))) == NULL) // remember the thing inside the if statement always runs so it will malloc it 
  {
    fprintf(stderr, "Insufficient memory for Set\n"); // print to stderr if malloced result is NULL
    exit(EXIT_FAILURE); 
  }
  s->nelems = 0;  // size of the set set to 0 elements 
  return s; 
}

void SetInsert(Set s, int item) 
{
  for (int i = 0; i < s->nelems; i++)
  {
    if (s->elems[i] == item)
    {
      return; 
    }
  } 
  s->elems[s->nelems] = item; 
  s->nelems++; 
}

void SetShow(Set s)
{
  printf("{"); // start the set 
  for (int i = 0; i < s->nelems; i++) // loop through the set and print all elements
  {
    printf("%d", s->elems[i]); 
    if (i < s->nelems - 1) // inserting a comma after every element except the last
    {
      printf(","); 
    }
  }
  printf("}"); 
}

void SetDelete(Set s, int item)
{
  for (int i = 0; i < s->nelems; i++)
  {
    if (s->elems[i] == item)
    {
      break; 
    }
    if (i < s->nelems)
    {
      s->elems[i] = s->elems[s->nelems - 1]; 
      s->nelems--; 
    }
  }
}

void SetDestroy(Set s)
{
  if (s != NULL)
  {
    free(s); 
  }
}

Set SetCopy (Set s)
{
  Set new; 
  new = SetCreate(); // create the new set 
  for (int i = 0; i < s->nelems; i++)
  {
    SetInsert(new, s->elems[i]); // 
  }
  new->nelems = s->nelems; 
  for (int i = 0; i < s->nelems; i++)
  {
    new->elems[i] = s->elems[i];
  }
  return new; 
}

