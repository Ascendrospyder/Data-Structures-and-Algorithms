
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

BSTree createNode(int value)
{
	BSTree t = malloc(sizeof(*t)); 
	t->value = value; 
	t->left = NULL; 
	t->right = NULL; 

	return t; 
}

BSTree BSTreeInsert(BSTree t, int val) {
	// TODO
	if (t == NULL)
	{
		return createNode(val); 
	} else if (t->value < val) {
		t->right = BSTreeInsert(t->right, val); 
	} else if (t->value > val) {
		t->left = BSTreeInsert(t->left, val); 
	}
	return t;
}

