#include <stdio.h>
#include <stdlib.h>


// Assumption: 0 <= a <= b < size of arr
int fnA(int arr[], int a, int b) {
    if (a == b) {
        return a;
    }
    int i = fnA(arr, a + 1, b);
    return (arr[a] < arr[i]) ? a : i;
}

// Assumption: 0 <= a <= b < size of arr
void fnB(int arr[], int a, int b) {
    if (a >= b) {
        return;
    }
    int i = fnA(arr, a, b);
    int temp = arr[a];
    arr[a] = arr[i];
    arr[i] = temp;
    fnB(arr, a + 1, b);
}

int main (void)
{
  int arr[5] = {1, 3, 4, 5, 6}; 
  int result = fnB(arr, 0, 5);
  printf("%d\n", result); 
  return 0; 
}