#include <stdio.h>
#include "set.h"

int main (void)
{
  Set s = SetCreate(); 

  for (int i = 0; i < 26; i += 2)
  {
    SetInsert(s, i); 
  }
  SetShow(s); 
  printf("\n"); 
  return 0; 
}