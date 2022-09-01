#include <stdio.h>

int function (int n); 

int x = 0; 
int main (void)
{
  int result1 = function(5); 
  printf("Result1 = %d\n", result1); 

  int result2 = function(5);
  printf("Result2 = %d\n", result2); // this result is 50 as since we have a global variable it will be added on to from the previous result
  return 0; 
}

int function (int n)
{
  // static int x = 0;  here we declare a static variable of 0 
  if (n > 0)
  {
    x++; // this will keep iterating however this calculation will only happen after n <= 0
    return function(n - 1) + x; 
  } else {
    return 0; 
  }
}