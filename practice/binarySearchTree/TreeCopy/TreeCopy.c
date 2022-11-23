
#include "tree.h"

Tree insertNode(int value)
{
	Tree new = malloc(sizeof(*new)); 
	new->left  = new->right = NULL; 
	new->value = value; 

	return new; 
}

int treeHeight(Tree t)
{
	if (t == NULL)
	{
		return 0; 
	} else {
		int lHeight = treeHeight(t->left) + 1; 
		int rHeight = treeHeight(t->right) + 1; 

		return lHeight > rHeight ? lHeight : rHeight; 
	}
}

Tree TreeCopy(Tree t, int depth) {
	// TODO
	if (depth < 0 || t == NULL)
	{
		return NULL; 
	} else {
		Tree tCopy = insertNode(t->value); 
		tCopy->left = TreeCopy(t->left, depth - 1); 
		tCopy->right = TreeCopy(t->right, depth - 1); 
		return tCopy;
	}
	 
}

