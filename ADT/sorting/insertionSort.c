#include <stdio.h>
#include <stdlib.h>

void printArray(int *array, int size); 
void insertionSort(int *a, int low, int high); 

int main (int argc, char** argv)
{
  printf("Before sorting:\n"); 
  int array[] = {2, 5, 7, 3, 23, 9, 1}; 
  int size = sizeof(array) / sizeof(array[0]); 
  printArray(array, size);

  printf("After sorting:\n"); 
  insertionSort(array, 0, 6); 
  printArray(array, size); 

  return 0; 
}

/*
  This function will perform a selection sort, where it will find the smallest element 
  and swap it to the first index of the unsorted section 
*/ 
void insertionSort(int *a, int low, int high)
{
  int i, j, value; // i will hold low + 1'th index, j will be a reference to compare the sorted section and value used to check if sorted section needs further swapping  
  for (i = low + 1; i <= high; i++) // we start at index low + 1 as we assume low'th index has been inserted 
  {
    printArray(a, high - low + 1); 
    value = a[i]; // make value point to current index 
    for (j = i; j > low; j--)
    {
      if (value > a[j - 1]) // if value is greater than the element before then continue 
      {
        break; 
      }
      a[j] = a[j - 1]; // else swap the element in the sorted section 
    }
    a[j] = value; 
  }
}

void printArray(int *array, int size) {
  for (int i = 0; i < size; ++i) {
    printf("%d  ", array[i]);
  }
  printf("\n");
}