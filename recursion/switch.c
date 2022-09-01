// This program will demonstrate the use of switch statements to clean up our code 
// We use switch statements when we have multiple if/else statments comparing the same condition 

#include <stdio.h>

int main (int argc, char *argv[])
{
  char *input = argv[1]; 
  // a switch statement will help us clean up if ... else if ... else if .... else types of code
  switch (*input)
  {
    case 'W': printf("Up\n"); break; // if (input == UP) print that 
    case 'S': printf("Down\n"); break; //else if (input == Down) print that 
    case 'A': printf("Left\n"); break; 
    case 'D': printf("Right\n"); break; 
    default: printf("Not Valid\n"); // else print not valid
  }

  return 0; 
}