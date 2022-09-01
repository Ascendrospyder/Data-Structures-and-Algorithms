#include <stdio.h>
#include <stdlib.h>

void function_recursive (int n);

int main (void) {
  int x = 3; 
  function_recursive(x);
  return 0;  
}

void function_recursive (int n) {
  if (n > 0) {
    printf("%d ", n); 
    function_recursive(n - 1);
  }
}