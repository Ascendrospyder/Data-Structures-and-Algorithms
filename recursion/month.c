#include <stdio.h>
#include <assert.h>
#include <string.h>

char *month_name(int month_num); 

int main (void)
{
  int month = 0; 
  printf("Please enter the month number you would like to see: "); 
  scanf(" %d", &month); 
  char *month_n = month_name(month); 
  printf("%s\n", month_n); 
  ///////////////////////////////////////Testing///////////////////////////////////////////////////////////////////
  assert(strcmp(month_name(1), "Jan") == 0); 
  assert(strcmp(month_name(2), "Feb") == 0);
  assert(strcmp(month_name(3), "Mar") == 0);
  assert(strcmp(month_name(4), "April") == 0);
  assert(strcmp(month_name(5), "May") == 0);
  assert(strcmp(month_name(6), "Jun") == 0);
  assert(strcmp(month_name(7), "Jul") == 0);
  assert(strcmp(month_name(8), "Aug") == 0);
  assert(strcmp(month_name(9), "Sep") == 0);
  assert(strcmp(month_name(10), "Oct") == 0);
  assert(strcmp(month_name(11), "Nov") == 0);
  assert(strcmp(month_name(12), "Dec") == 0);
  return 0; 
}

char *month_name(int month_num)
{
  switch(month_num)
  {
    case 1: 
      return "Jan";   
    case 2:
      return "Feb";   
    case 3:
      return "Mar";  
    case 4:
      return "April";   
    case 5:
      return "May";  
    case 6:
      return "Jun";  
    case 7:
      return "Jul";  
    case 8:
      return "Aug";  
    case 9:
      return "Sep";  
    case 10:
      return "Oct";  
    case 11:
      return "Nov";  
    case 12:
      return "Dec";  
  }
  return NULL; 
}