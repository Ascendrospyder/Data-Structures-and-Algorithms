#define TRUE 1 
#define FALSE 0 
#define MAX_NUMS 10000
#include <stdio.h>

void bubblesort (int *nums, int size); 
int main (void)
{
  int input[MAX_NUMS];
  int count = 0; 

  while(scanf("%d", &input[count]) != -1)
  {
    count++; 
  } 
  printf("Array before sorting: "); 
  for (int i = 0; i < count; i++)
  {
    printf("%d ", input[i]); 
  }
  printf("\n"); 
  bubblesort(input, count);
  printf("Array after sorting: "); 
  for (int j = 0; j < count; j++)
  {
    printf("%d ", input[j]); 
  } 
  printf("\n"); 
  return 0; 
}
void bubblesort (int *nums, int size)
{
  int sort = FALSE; // declare a flag where the sort is false 
  while (sort == FALSE) // while the flag is still false loop through the list 
  {
    sort = TRUE; // we declare its true, ok now prove it to me 
    for (int i = 0; i < size - 1; i++)
    {
      if (nums[i] > nums[i + 1]) // if the number in front is bigger then sort it 
      {
        int temp = nums[i]; // create a temp variable and load in nums[i]
        nums[i] = nums[i + 1]; // swap them 
        nums[i + 1] = temp; // redeclare the next number as temp and declare sorted as false so we can check for the next element 
        sort = FALSE; 
      }
    }
  }
}