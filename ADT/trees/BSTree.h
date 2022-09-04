
typedef struct Node *Tree; // we create our data structure using a typedef 

typedef int Item; 

Tree TreeCreate(Item it); // creates the tree
void TreeFree(Tree t);  // free's the tree
Tree TreeInsert(Tree t, Item it); // inserts node inside of tree
void ShowTree(Tree t); // prints the tree out 