#include <stdio.h>

void month_name(int month_num); 

int main (void)
{
  int month = 0; 
  printf("Please enter the month number you would like to see: "); 
  scanf(" %d", &month); 
  month_name(month); 
  return 0; 
}

void month_name(int month_num)
{
  switch(month_num)
  {
    case 1: 
      printf("Jan\n"); 
      break; 
    case 2:
      printf("Feb\n"); 
      break; 
    case 3:
      printf("March\n"); 
      break; 
    case 4:
      printf("April\n"); 
      break; 
    case 5:
      printf("May\n"); 
      break; 
    case 6:
      printf("Jun\n");
      break; 
    case 7:
      printf("Jul\n"); 
      break; 
    case 8:
      printf("Aug\n"); 
      break; 
    case 9:
      printf("Sep\n"); 
      break; 
    case 10:
      printf("Oct\n"); 
      break; 
    case 11:
      printf("Nov\n"); 
      break; 
    case 12:
      printf("Dec\n");
      break; 
    default:
      printf("Error, please enter a valid month number.\n"); 
  }
}