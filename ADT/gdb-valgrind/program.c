// this program will basically be used to debug using GDB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printChar(char c); 

int main (int argc, char **argv)
{
  char *s = "Good luck with the assignment"; 
  for (int i = 0; i < strlen(s); i++)
  {
    printChar(s[i]);  
  }
  return 0; 
}

void printChar(char c)
{
  putchar(c); 
  printf("\n");
}