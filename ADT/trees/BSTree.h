
typedef struct Node *Tree; // we create our data structure using a typedef 

typedef int Item; 

Tree TreeCreate(Item it); // creates the tree
void TreeFree(Tree t);  // free's the tree
Tree TreeInsert(Tree t, Item it); // inserts node inside of tree
void ShowTree(Tree t); // prints the tree out 
Tree TreeJoin(Tree t, Tree n); // joins two trees together 
Tree TreeDelete(Tree t, Item it); 
void FreeTree(Tree t); 
Tree TreeRotateRight(Tree t); 
Tree TreeRotateLeft(Tree t); 
Tree InsertAtRoot(Tree t, Item it); 