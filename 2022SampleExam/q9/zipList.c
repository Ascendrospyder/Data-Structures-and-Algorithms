
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void append(List l, int item)
{
    Node new = newNode(item); 
    if (l->first == NULL)
    {
        l->first = new; 
        l->last = new; 
    } else {
        l->last->next = new; 
        l->last = new; 
    }
}

// Worst case time complexity of this solution: O(...)
/*
    steps: 
    1. first check if l1 is empty, then return l2
    2. if l2 is empty return l1 
    3. if both are empty return an empty list
    4. create current pointers to the head of l1 and l2 
    5. 
*/
List zipList(List l1, int x, List l2, int y) {
    // TODO
    if (l1 == NULL)
    {
        return l2;  
    } else if (l2 == NULL) {
        return l1; 
    } else if (l1 == NULL && l2 == NULL) {
        return ListNew(); 
    }
    
    List new = ListNew(); 
    Node current1 = l1->first; 
    Node current2 = l2->first; 

    while (current1 != NULL && current2 != NULL && x >= 0 && y >= 0)
    {
        int count1 = 0; 
        while (current1 != NULL && count1 < x)
        {
            append(new, current1->value); 
            current1 = current1->next; 
            count1++;
        }

        int count2 = 0; 
        while (current2 != NULL && count2 < y)
        {
            append(new, current2->value); 
            current2 = current2->next; 
            count2++; 
        }
    }

    // if we reach a point where one list is NULL, we 
    // just append current1 into new list 
    while (current1 != NULL && x > 0)
    {
        append(new, current1->value); 
        current1 = current1->next; 
    }

    while (current2 != NULL && y > 0)
    {
        append(new, current2->value); 
        current2 = current2->next; 
    }
    

    return new;
}

