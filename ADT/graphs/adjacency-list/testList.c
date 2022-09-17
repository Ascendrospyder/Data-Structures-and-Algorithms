#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main (int argc, char **argv) {
    struct Node *new_node = makeNode(5);
    List a = insertLL(new_node, 3);
    a = insertLL(a, 6);
    a = insertLL(a, 2);
    a = insertLL(a, 100);
    a = insertLL(a, 4);
    a = insertLL(a, 4);
    printf("Adding elements into LL:\n"); 
    showLL(a); 
    List b = deleteLL(a, 2);
    printf("Deleting elements from LL:\n");     
    showLL(b); 
}