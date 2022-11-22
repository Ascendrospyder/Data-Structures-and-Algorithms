
#include <stdlib.h>

#include "tree.h"

int TreeHeight(Tree t) {
   if (t == NULL) {
      return -1;
   } else {
      int lheight = 1 + TreeHeight(t->left);
      int rheight = 1 + TreeHeight(t->right);
      if (lheight > rheight)
   return lheight ;
      else
   return rheight;
   }
}

