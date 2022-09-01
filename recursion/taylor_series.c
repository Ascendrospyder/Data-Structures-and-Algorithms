#include <stdio.h>

int taylor_sum (int x, int n); 

int main (void)
{
  int x = 0; 
  int n = 0; 
  printf("Please enter the power of the exponential function and the nth value for which we find the sum respectively: "); 
  scanf(" %d %d", &x, &n); 
  int result = taylor_sum(x, n); 
  printf("The result of the taylor sum of e is %d.\n", result); 
  return 0; 
}

int taylor_sum (int x, int n)
{
  static int p = 1; 
  static int f = 1; 
  
  if (n == 0)
  {
    return 0; 
  } else {
    int result = taylor_sum(x, n - 1); 
    p = p * x; 
    f = f * n; 
    return result + (p / f); 
  }
}