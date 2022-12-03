
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

List flas(List l) {
    // TODO
    if (l == NULL)
    {
        NULL; 
    }

    List current = l; 
    List flas = ListNew(); 
     
    int flasCount = 0; 
   
    while (current != NULL)
    {
        List start = current; 
        int count = 1;
        printf("start = %d\tcurrent = %d\tcount = %d\n", start->value, current->value, count);
        
        while (current->next != NULL && current->value < current->next->value)
        {
            
            count++; 
            
            current = current->next; 
        }
        
        if (count > flasCount && count >= 2)
        {
            flas = start;  
            flasCount = count; 
        }
        current = current->next; 
    }

    return flas;
}

