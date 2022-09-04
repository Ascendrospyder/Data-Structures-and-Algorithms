#include <stdio.h>
#include <stdlib.h>

#define MAX 256

void binary_search(int lowest, int highest, int key, int array[MAX]); 
int recursive_binary_search (int low, int high, int key, int array[MAX]); 

int main (void)
{
  int array[] = {102, 118, 124, 131, 140, 148, 161, 166, 176, 180}; 
  int size = sizeof(array)/sizeof(int); 
  // printf("size = %d", size); 
  binary_search(0, size, 118, array); 
  printf("found in index %d\n", recursive_binary_search(0, size, 118, array)); 

  return 0; 
}

void binary_search(int lowest, int highest, int key, int array[MAX])
{
  while (lowest <= highest) // loop until our highest is never less than the lowest 
  {
    int mid = (lowest + highest) / 2; // declare the mid point 
    printf("Lowest = %d\nHighest = %d\nkey = %d\nmid pos = %d\nmid value = %d\n", lowest, highest, key, mid, array[mid]); 
    if (key == array[mid]) // if we find the element print element found and return from function 
    {
      printf("Element found!\n"); 
      return;
    } else if (key < array[mid]) { // if key is before the mid point, make the highest, mid - 1 and continue the algorithm
      highest = mid - 1; 
    } else { // if key is after mid point new lowest = mid + 1 and continue finding it 
      lowest = mid + 1; 
    }
  }
}

  
int recursive_binary_search (int lowest, int highest, int key, int array[MAX])
{
  if (lowest <= highest)
  {
    int mid = (lowest + highest) / 2; 
    if (key == array[mid]) 
    {
      return mid;
    } else if (key < array[mid]) {
      return recursive_binary_search(lowest, mid - 1, key, array); 
    } else {
      return recursive_binary_search(mid + 1, highest, key, array); 
    }
  } 
  return -1; 
}