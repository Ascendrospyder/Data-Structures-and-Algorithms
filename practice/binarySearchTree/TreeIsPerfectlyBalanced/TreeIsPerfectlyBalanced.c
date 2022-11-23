
#include <stdlib.h>
#include <stdio.h>

#include "tree.h"

int findHeight(Tree t)
{
	if (t == NULL)
	{
		return 0; 
	} else {
		return 1 + findHeight(t->left) + findHeight(t->right); 
	}
}
bool TreeIsPerfectlyBalanced(Tree t) {
	// TODO
	if (t == NULL)
	{
		return true; 
	} else {
		int lHeight = findHeight(t->left); 
		int rHeight = findHeight(t->right); 

		if (lHeight - rHeight > 1 || rHeight - lHeight > 1)
		{
			return false; 
		} else {
			return TreeIsPerfectlyBalanced(t->left) && TreeIsPerfectlyBalanced(t->right); 
		}
	}

}

