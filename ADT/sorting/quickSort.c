#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printArray(int *array, int size); 
void quickSort(int *a, int low, int high);
void swapElement(int *a, int i, int j); 
int partition(int *a, int low, int high);

int main (int argc, char** argv)
{
  printf("Before sorting:\n"); 
  int array[] = {2, 5, 7, 3, 23, 9, 1}; 
  int size = sizeof(array) / sizeof(array[0]); 
  // printf("Before sorting:\n"); 
  printArray(array, size);

  printf("After sorting:\n"); 
  quickSort(array, 0, 6); 
  printArray(array, size); 

  return 0; 
}

/*
  This function will perform a selection sort, where it will find the smallest element 
  and swap it to the first index of the unsorted section 
*/ 
void quickSort(int *a, int low, int high)
{
  if (high <= low) 
  {
    return; 
  }
  int i = partition(a, low, high); 
  quickSort(a, low, i - 1); 
  quickSort(a, i + 1, high); 
}

void printArray(int *array, int size) {
  for (int i = 0; i < size; ++i) {
    printf("%d  ", array[i]);
  }
  printf("\n");
}

int partition(int *a, int low, int high)
{
  int pivot = a[low]; 
  int i = low + 1; // we start from the element after the pivot 
  int j = high; // starts from the end of the array 

  for (; ;)
  {
    while (a[i] < pivot && i < j)
    {
      i++; 
    }
    while (pivot < a[j])
    {
      j--; 
    }
    if (i == j) break; 
    swapElement(a, i, j); 
  }
  j = (a[i] < pivot) ? i : i - 1; 
  swapElement(a, low, j); 
  return j; 
}

void swapElement(int *a, int i, int j)
{
  int temp = a[i]; 
  a[i] = a[j]; 
  a[j] = temp; 
}