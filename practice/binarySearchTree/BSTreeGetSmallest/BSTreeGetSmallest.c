
#include "BSTree.h"

#include <stdlib.h>
#include <stdio.h>


/*
	steps:
	1. the smallest value will be the left most in the tree 
*/
BSTree BSTreeGetSmallest(BSTree t) {
	// TODO
	if (t == NULL)
	{
		return NULL;
	} else if (t->left != NULL)
	{ 
		return BSTreeGetSmallest(t->left); 
	} else {
		return t;
	}
 
}

