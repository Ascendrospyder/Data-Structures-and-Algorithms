#include <stdio.h>

int fibonacci (int n); 

int main (void) 
{
  int n = 0; 
  printf("Please enter how big you want us to calculate the fibonacci sum of: "); 
  scanf(" %d", &n); 
  int result = fibonacci(n); 
  printf("The sum of the %dth fibonacci element is %d.\n", n, result); 
  return 0; 
}

int fibonacci (int n) 
{
  if (n <= 1)
  {
    return n; 
  } else {
    return fibonacci(n - 1) + fibonacci(n - 2); 
  }
}