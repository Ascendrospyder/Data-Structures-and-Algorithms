#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hash.h"

int main (int argc, char **argv)
{
    HashTable t = newHashTable(20);
    HashInsert(t, "ello");
    Item *result = HashGet(t, "ello");
    printf("%s\n", result);    
    return 0; 
}