// Implementation of the Tree ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Record.h"
#include "Tree.h"

typedef struct node *Node;
struct node {
	Record rec;
	Node left;
	Node right;
	// IMPORTANT: Do not modify the fields above
	// You may add additional fields below if necessary
	int height_left;
	int height_right;
};

struct tree {
	Node root;
	int (*compare)(Record, Record);

	// IMPORTANT: Do not modify the fields above
	// You may add additional fields below if necessary
};

static void doTreeFree(Node n, bool freeRecords);

////////////////////////////////////////////////////////////////////////
// Provided functions
// !!! DO NOT MODIFY THESE FUNCTIONS !!!

Tree TreeNew(int (*compare)(Record, Record)) {
	Tree t = malloc(sizeof(*t));
	if (t == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	t->root = NULL;
	t->compare = compare;
	return t;
}

void TreeFree(Tree t, bool freeRecords) {
	doTreeFree(t->root, freeRecords);
	free(t);
}

static void doTreeFree(Node n, bool freeRecords) {
	if (n != NULL) {
		doTreeFree(n->left, freeRecords);
		doTreeFree(n->right, freeRecords);
		if (freeRecords) {
			RecordFree(n->rec);
		}
		free(n);
	}
}

////////////////////////////////////////////////////////////////////////
// Functions you need to implement

////////////////////////// function declarations //////////////////////
static int getHeight(Node n);
static Node TreeRotateRight(Node n);
static Node TreeRotateLeft(Node n);
static Node doTreeInsert(Tree t, Record rec, Node n, bool *result);
static Node createNewNode(Record rec);
static Record doTreeSearch(Tree t, Node n, Record rec);
static void doTreeSearchBetween(Tree t, Node n, Record lower, Record higher,
                                List l);
static void doTreeNext(Tree t, Node n, Record rec, Record *next);
// static void printTree(Tree t);
////////////////////////// function declarations //////////////////////

/**
 * @brief - This function is used for inserting a record into the tree and 
 * updating it as true or false if it has or hasn't been inserted, respectively. 
 * 
 * @param t - Tree 
 * @param rec - Record 
 * @return true - if the record has been inserted into the tree
 * @return false - if the record has not been inserted into the tree 
 */
bool TreeInsert(Tree t, Record rec) {
	// basically an implementation of an AVL tree
	bool result = true;
	t->root = doTreeInsert(t, rec, t->root, &result);
	return result;
}

/**
 * @brief - This function will utilise the doTreeSearch function to check if a
 *  record exists in a tree
 * 
 * @param t - Tree
 * @param rec - Record 
 * @return Record - returns record if it exists or else NULL
 */
Record TreeSearch(Tree t, Record rec) {
	return doTreeSearch(t, t->root, rec);
}

/**
 * @brief - Given a lower and upper bound this function will return a list of 
 * all the records in between.
 * 
 * @param t - Tree
 * @param lower - Record 
 * @param upper - Record 
 * @return List - new list 
 */
List TreeSearchBetween(Tree t, Record lower, Record upper) {
	List l = ListNew();
	doTreeSearchBetween(t, t->root, lower, upper, l);
	return l;
}

/**
 * @brief - Returns the smallest record that is greater than or equal to the 
 * given record, or NULL if there is no such record.
 * 
 * @param t - Tree 
 * @param rec - Record
 * @return Record - smallest record 
 */
Record TreeNext(Tree t, Record rec) {
	Record next = NULL;
	doTreeNext(t, t->root, rec, &next);
	return next;
}
////////////////////////////////////////////////////////////////////////
/////////////////////////// HELPER FUNCTIONS //////////////////////////
/**
 * @brief - This function will create a new node when the function is called
 * 
 * @param rec - Record 
 * @return Node - new Node
 */
static Node createNewNode(Record rec) {
	Node new_node = malloc(sizeof(*new_node));

	if (new_node == NULL) {
		fprintf(stderr, "Failed to allocate memory\n");
		exit(EXIT_FAILURE);
	}

	// populate the struct with appropriate values
	new_node->rec = rec;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->height_left = 0;
	new_node->height_right = 0;

	return new_node;
}

/**
 * @brief - gets the height of a Node
 * 
 * @param n - Node
 * @return int - height of node given  
 */
static int getHeight(Node n) {
	// adapted from lecture code on avl trees
	if (n == NULL) {
		return 0;
	} else {
		n->height_left = 1 + getHeight(n->left);
		n->height_right = 1 + getHeight(n->right);

		if (n->height_left > n->height_right) {
			return n->height_left;
		} else {
			return n->height_right;
		}
	}
}

/**
 * @brief - The following function when given a node will rotate the node 
 * to the right 
 * 
 * @param n - Node n 
 * @return Node - Node that has been rotated to the right 
 */
static Node TreeRotateRight(Node n) {
	// The following code was adapted from the lecture code on tree rotations
	Node current = n->left;  // set up a new root and make it point to the left tree
	if (n == NULL || current == NULL)  // if trees our empty return our original tree
	{
		return n;
	} else {
		n->left = current->right;
		current->right = n;
		return current;
	}
}

/**
 * @brief - The following function, given a node will rotate it to the left
 * 
 * @param n - Node n 
 * @return Node - Node rotated to the left 
 */
static Node TreeRotateLeft(Node n) {
	// The following code was adapted from the lecture code on tree rotations
	Node current = n->right;  // setup a current node which will point to n->right
	if (n == NULL || current == NULL)  // if the node, or current doesn't exist return n
	{
		return n;
	} else {
		n->right = current->left;  // assigns n->right with the
		current->left = n;
		return current;
	}
}

/**
 * @brief - The following function is a helper function for TreeInsert and will basically
 * perform the insertion. Inserts a record into the tree. 
 * 
 * @param t - Tree t
 * @param rec - Record rec 
 * @param n - Node n 
 * @param result - bool *result 
 * @return Node - node to insert 
 */
static Node doTreeInsert(Tree t, Record rec, Node n, bool *result) {
	if (n == NULL)  // if the tree doesn't exist, create it and return true
	{
		Node newNode = createNewNode(rec);
		return newNode;
	}

	int compare = t->compare(rec, n->rec);

	// the following code will insert into correct position
	if (compare == 0)  // if the rec and our rec are the same then no need to insert
	{
		*result = false;
		return n;
	} else if (compare < 0) {  // if the rec is is less than our rec then traverse the left section
		n->left = doTreeInsert(t, rec, n->left, result);
	} else {  // else we must traverse the right section
		n->right = doTreeInsert(t, rec, n->right, result);
	}

	int lheight = getHeight(n->left);
	int rheight = getHeight(n->right);

	// the following code will rebalance the inserted node and is an adapted version of the lecture code on avl trees
	if ((lheight - rheight) > 1)  // if the balance factor is unbalanced then proceed below
	{
		int compare_left = t->compare(rec, n->left->rec);
		if (compare_left > 0)  // this means the item will be positioned to the right of the t->left section, to balance this we need to rotate it to the left
		{
			n->left = TreeRotateLeft(n->left);
		}
		n = TreeRotateRight(n);  // after rotating to the left we need to rotate it to the right to ensure balance
	} else if ((rheight - lheight) > 1) {
		int compare_right = t->compare(rec, n->right->rec);
		if (compare_right < 0)  // this is a RL imbalance, therfore we need to first rotate to the right and then left
		{
			n->right = TreeRotateRight(n->right);
		}
		n = TreeRotateLeft(n);
	}
	return n;
}

/**
 * @brief - the following function is a helper function for TreeSearch. 
 * 
 * @param t - Tree t 
 * @param n - Node n 
 * @param rec - Record rec 
 * @return Record 
 */
static Record doTreeSearch(Tree t, Node n, Record rec) {
	if (n == NULL)  // if the record doesn't exist return NULL
	{
		return NULL;
	}

	int compare = t->compare(rec, n->rec);  // make the comparison between the record of interest and our record

	if (compare < 0)  // if record of interest is less than current record, traverse left section of tree
	{
		return doTreeSearch(t, n->left, rec);
	} else if (compare > 0) {  // if record of interest is more than current record, traverse right section of tree
		return doTreeSearch(t, n->right, rec);
	} else {  // if we found the record return the current record
		return n->rec;
	}
}

/**
 * @brief - The following function is the helper function for TreeSearchBetween. 
 * 
 * @param t - Tree t
 * @param n - Node n 
 * @param lower - Record lower bound 
 * @param upper - Record upper bound 
 * @param l - List l 
 */
static void doTreeSearchBetween(Tree t, Node n, Record lower, Record upper,
                                List l) {
	// the code has been adapted from my lab04 code
	if (n == NULL) {
		return;
	}

	int compare_lower = t->compare(lower, n->rec);
	int compare_higher = t->compare(upper, n->rec);

	// to have an inorder traversal, left -> root -> right

	if (compare_lower < 0)  // if the record is higher than the lower bound, traverse left section
	{
		doTreeSearchBetween(t, n->left, lower, upper, l);
	}

	if (compare_higher >= 0 && compare_lower <= 0)  // else go ahead and add to the list!
	{
		ListAppend(l, n->rec);
	}

	if (compare_higher > 0)  // if the record is higher than the higher bound, traverse right section
	{
		doTreeSearchBetween(t, n->right, lower, upper, l);
	}
}

/**
 * @brief - The following function is a helper function for TreeNext. 
 * 
 * @param t - Tree t 
 * @param n - Node n  
 * @param rec - Record rec 
 * @param next - Record *next 
 */
static void doTreeNext(Tree t, Node n, Record rec, Record *next) {
	if (n == NULL) return;

	int compare = t->compare(rec, n->rec);

	if (compare > 0)  // if the record of interest is higher than our current record then traverse right subtree
	{
		return doTreeNext(t, n->right, rec, next);
	} else {  // if the record of interest is lower than our current record then traverse left subtree
		*next = n->rec;  // update the next address to hold the current record
		return doTreeNext(t, n->left, rec, next);
	}
}
////////////////////////////////// testing //////////////////////////////////////////////////////

// /**
//  * @brief - The following function is the helper function for printTree for further debugging.
//  *
//  * @param n - Node n
//  */
// static void doPrintTree(Node n)
// {
//     if (n == NULL) return;

//     // preorder print
//     printf("%s| %s | %s |%d %d00 | %d\n", RecordGetFlightNumber(n->rec), RecordGetDepartureAirport(n->rec),
//                                             RecordGetArrivalAirport(n->rec),  RecordGetDepartureDay(n->rec),
//                                             RecordGetDepartureHour(n->rec), RecordGetDurationMinutes(n->rec));
//     doPrintTree(n->left);
//     doPrintTree(n->right);
// }

// /**
//  * @brief - The following function basically prints the tree out for debugging to check if insertion
//  * is correct.
//  *
//  * @param t - Tree t
//  */
// static void printTree(Tree t)
// {
//     doPrintTree(t->root);
//     printf("\n");
// }