#include <stdio.h>
#include <stdlib.h>

void printArray(int *array, int size); 
void mergeSort(int *a, int low, int high);
void merge(int *a, int low, int mid, int high);  

int main (int argc, char** argv)
{
  printf("Before sorting:\n"); 
  int array[] = {2, 5, 7, 3, 23, 9, 1}; 
  int size = sizeof(array) / sizeof(array[0]); 
  // printf("Before sorting:\n"); 
  printArray(array, size);

  printf("After sorting:\n"); 
  mergeSort(array, 0, 6); 
  printArray(array, size); 

  return 0; 
}

/*
  This function will perform a selection sort, where it will find the smallest element 
  and swap it to the first index of the unsorted section 
*/ 
void mergeSort(int *a, int low, int high)
{
  int mid = (low + high) / 2; 

  if (high <= low)
  {
    return; 
  }

  mergeSort(a, low, mid); 
  mergeSort(a, mid + 1, high); 
  merge(a, low, mid, high); 
}

void printArray(int *array, int size) {
  for (int i = 0; i < size; ++i) {
    printf("%d  ", array[i]);
  }
  printf("\n");
}

void merge(int *a, int low, int mid, int high)
{
  int i, j, k, nItems = high - low + 1; 

  int *current = malloc(nItems *sizeof(int)); // we need to create a new array which will hold our merged result 

  i = low; j = mid + 1; k = 0; 

  while (i <= mid && j <= high)
  {
    if (a[i] < a[j])
    {
      current[k++] = a[i++];
    } else {
      current[k++] = a[j++]; 
    }
  }

  while (i <= mid) 
  {
    current[k++] = a[i++]; 
  }

  while (j <= high)
  {
    current[k++] = a[j++]; 
  }

  for (i = low, k = 0; i <= high; i++, k++)
  {
    a[i] = current[k]; 
  }
  free(current); 
}