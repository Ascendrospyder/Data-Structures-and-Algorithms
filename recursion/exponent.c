#include <stdio.h>

int exponent (int m, int n); 

int main (void)
{
  int m = 0; 
  int n = 0; 
  printf("Enter the base and power of the number you want to calculate for respectively: "); 
  scanf(" %d %d", &m, &n); 
  int result = exponent(m, n); 
  printf("%d to the power of %d is %d.\n", m, n, result); 
  return 0; 
}

int exponent (int m, int n)
{
  if (n == 0) 
  {
    return 1; 
  } else {
    return exponent(m, n - 1) * m; 
  }
}