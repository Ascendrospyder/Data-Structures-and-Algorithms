#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


bool isSorted(int *a, int n); 

int main (int argc, char **argv)
{
  int array[5] = {2, 7, 3, 6, 3}; 
  if (isSorted(array, 5) == false)
  {
    printf("Array is not sorted\n"); 
  } else if (isSorted(array, 5) == true) {
    printf("Sorted\n"); 
  }
  return 0; 
}

bool isSorted(int *a, int n) {
  int sort = false; 
  while (sort == false)
  {
    for (int i = 0; i < n - 1; i++)
    {
      if (a[i] > a[i + 1])
      {
        return false; 
      } else {
        return true; 
      }
    }
  }
  return false; 
}