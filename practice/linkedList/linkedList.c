#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data; 
  struct node *next; 
} Node; 

Node *createLL(int data)
{
  Node *new_list = malloc(sizeof(Node)); 

  new_list->data = data; 
  new_list->next = NULL; 

  return new_list; 
}

void insertLL(Node *list, int data)
{
  Node *new_node = malloc(sizeof(Node *)); 
  Node *current = list; 

  while (current != NULL)
  {
    current = current->next; 
  }
  
  new_node->data = data; 
  new_node->next = NULL; 

}

void printList(Node *list)
{
  Node *current = list; 

  while (current != NULL)
  {
    printf("%d ", current->data); 
    current = current->next; 
  }
  printf("\n"); 
  return; 
}

int main (int argc, char **argv)
{
  Node *new = createLL(3); 
  insertLL(new, 8); 
  printList(new); 
}