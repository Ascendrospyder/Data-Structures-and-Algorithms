// this file basically sets the ADT's
#ifndef SET_H
#define SET_H

#include <stdbool.h>

typedef struct SetRep *Set; 

Set SetCreate();  // create a newset
void SetInsert(Set, int);  //add number into a set
void SetDelete(Set, int);  // remove number from set 
int SetMember(Set, int);  // set membership test
int SetCard(Set);  // size of set 
Set Union(Set, Set);  // find the union of two sets 
Set SetIntersect(Set, Set);   // intersection of two sets 
void SetDestroy(Set);  // destroy a created set

Set SetCopy(Set); // make a copy of the set
void SetShow(Set); // display set to stdout

#endif 