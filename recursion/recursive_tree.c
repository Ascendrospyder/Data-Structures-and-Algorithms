#include <stdio.h>

void tree_fun (int n)
{
  if (n > 0)
  {
    printf("%d ", n); 
    tree_fun(n - 1); 
    tree_fun(n - 1); 
  } 
}
int main (void)
{
  tree_fun(3); 
  printf("\n");
  return 0; 
}