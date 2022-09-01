#include <stdio.h>

int nested_fun (int n); 
int main (void)
{
  printf("%d ", nested_fun(91)); 
  return 0; 
}

int nested_fun (int n)
{
  if (n > 100)
  {
    return n - 10; 
  } else {
    return nested_fun(nested_fun(n + 11)); 
  }
} 