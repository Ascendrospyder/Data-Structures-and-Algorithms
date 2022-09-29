#include <stdio.h>
#include <stdlib.h>

void printArray(int *array, int size); 
void selectionSort(int *a, int low, int high); 

int main (int argc, char** argv)
{
  printf("Before sorting:\n"); 
  int array[] = {2, 5, 7, 3, 23, 9, 1}; 
  int size = sizeof(array) / sizeof(array[0]); 
  printArray(array, size);

  printf("After sorting:\n"); 
  selectionSort(array, 0, 6); 
  printArray(array, size); 

  return 0; 
}

/*
  This function will perform a selection sort, where it will find the smallest element 
  and swap it to the first index of the unsorted section 
*/ 
void selectionSort(int *a, int low, int high)
{
  int i, j, min; 
  for (i = low; i < high - 1; i++) // loop through low to high - 1, this being as high will already be sorted so no need to check 
  {
    min = i; // set min as i 
    for (j = i + 1; j <= high; j++) // this j element will loop through the whole array and find the smallest element 
    {
      if (a[j] < a[min]) // if the jth index is less than the min'th index then go ahead and make min point to j
      {
        min = j; 
      }
    }
    // now we will swap the ith index with the min'th index 
    int temp = a[i]; 
    a[i] = a[min]; 
    a[min] = temp; 
  }
}

void printArray(int *array, int size) {
  for (int i = 0; i < size; ++i) {
    printf("%d  ", array[i]);
  }
  printf("\n");
}