
#include <stdlib.h>
#include <stdio.h>

#include "tree.h"

/*
	steps : 
	1. for the root verify if the value is odd, if it is, then go ahead and 
	add value to our sum 
	2. then go to the left of the tree and verify that
	3. then the right 

*/
int TreeSumOdds(Tree t)
{
	if (t == NULL)
	{
		return 0; 
	} else if ((t->value % 2) == 1) {
		return t->value + TreeSumOdds(t->left) + TreeSumOdds(t->right); 
	} else {
		return TreeSumOdds(t->left) + TreeSumOdds(t->right); 
	}
}

