#include <stdio.h>

int sum_natural_nums (int n);

int main (void)
{ 
  int n = 0; 
  printf("Please enter the nth amount of natural numbers you would wish to find the sum of: "); 
  scanf(" %d", &n); 
  int result = sum_natural_nums(n); 
  printf("The sum of the first %d numbers is %d.\n", n, result); 
  return 0; 
}

int sum_natural_nums (int n) 
{
  if (n == 0)
  {
    return 0; 
  } else {
    return sum_natural_nums(n - 1) + n; 
  }
}

// time complexity = O(n)  space complexity = O(n) because it creates n activation records in stack 