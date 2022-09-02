// this program will create and display all the elements inside a linked list 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct node {
  int data; // stores the data in the node 
  struct node *next; // stores the next address in that node 
}; 

void print_list (struct node *head); 
struct node *create_list (int array[], int n); 
int length_recursive(struct node *head); 

int main (void)
{
  int array[] = {1, 2, 3, 6, 8}; 
  struct node *p = malloc(sizeof(struct node)); // since nodes are created in the heap we need to manually allocate memory 
  p = create_list(array, 5); 
  printf("length = %d\n", length_recursive(p)); 
  printf("Here is the linked list: "); 
  print_list(p); 
  printf("\n"); 
  return 0; 
}

void print_list (struct node *head)
{
  struct node *current = head; // we create a temporary node pointing to the head hence we can traverse the list 
  while (current != NULL) // don't put while current->next != NULL as it will move to the next element from current 
  {
    printf("%d ", current->data); 
    current = current->next; // iterate through all the nodes until we reach the tail
  }
  return; 
}

struct node *create_list (int array[], int n)
{
  struct node *tail; 
  struct node *head = malloc(sizeof(struct node)); 
  head->data = array[0]; // get the data of the first element inside that array
  head->next = NULL; // since its the first element it points to nothing 
  tail = head; 

  for (int i = 1; i < n; i++)
  {
    struct node *temp = malloc(sizeof(struct node));
    temp->data = array[i]; 
    temp->next = NULL; 
    tail->next = temp; 
    tail = temp; 
  }
  return head; 
}

// this function finds the length of a LL recursively 
int length_recursive(struct node *head)
{
  if (head == NULL) // base case - if head is doesnt exist the length should be 0 
  {
    return 0; 
  } else {
    return 1 + length_recursive(head->next); // we add 1 as the length will initially be 0 and we add 1 to that to account for the first count
  }
}