
#include <stdlib.h>
#include <stdio.h>

#include "BSTree.h"

int numNodes(BSTree t)
{
	if (t == NULL)
	{
		return 0; 
	} else {
		return 1 + numNodes(t->left) + numNodes(t->right); 
	}
}

/*
	memorise this 
*/
int BSTreeGetKth(BSTree t, int k) 
{
	// TODO

	int leftIndex = numNodes(t->left); 
	if (k == leftIndex)
	{
		return t->value; 
	} else if (leftIndex > k) {
		return BSTreeGetKth(t->left, k); 
	} else {
		return BSTreeGetKth(t->right, k - leftIndex - 1); 
	}
}

