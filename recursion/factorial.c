#include <stdio.h>

int factorial (int n); 

int main (void)
{
  int n = 0; 
  printf("Please enter in the nth factorial you which to find: "); 
  scanf(" %d", &n); 
  int result = factorial(n); 
  printf("The %dth factorial is %d.\n", n, result); 
  return 0; 
}

int factorial (int n)
{ 
  if (n == 0 || n == 1)
  {
    return 1; 
  } else if (n > 1) {
    return factorial(n - 1) * n; 
  } else {
    return 0; 
  }
}

// timecomplexity = O(n) and space complexity = O(n) since there are n amounts of activation records created in stack 