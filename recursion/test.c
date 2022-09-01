// In this program we will utilise the assert library to test our program 
// assert basically has a condition inside it and if it fails it will crash the program and if it passes the program will continue 
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0 

int is_even(int num); 
void test_is_even(); 

int main (void)
{
  test_is_even(); 
  return 0; 
}

int is_even (int num)
{
  if (num % 2 == 0) // if I make this 1 the assert spits an error
  {
    return TRUE; 
  } else {
    return FALSE; 
  }
} 

void test_is_even()
{
  assert(is_even(2) == TRUE); // if this statement is correct go ahead and have no issues however if its wrong then it will spit an error
  assert(is_even(3) == FALSE); 
}

