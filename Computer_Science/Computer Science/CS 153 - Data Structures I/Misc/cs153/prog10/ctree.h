
// Program 10: Binary tree demonstration (header for CTree)
// Erin Pringle and Joe Wingbermuehle
// This is a program to demonstrate a binary tree

#ifndef CTREE_H
#define CTREE_H

#include "stdafx.h"

class CTree {
public:

	// The data type for the items of the tree
	typedef int DType;

	// Constructor
	// PRE: none
	// POST: creates a new, empty tree
	CTree();

	// Destructor
	// PRE: none
	// POST: deletes all nodes from the tree
	~CTree();

	// Insert an item to the tree
	// PRE: value is the item to insert
	// POST: inserts the item, returns 1 on success, 0 on failure
	int insert(const DType& value);

	// Remove an item from the tree
	// PRE: value is the item to remove
	// POST: removes value from the tree (if possible), returns 1 if found
	//       0 if not found
	int remove(const DType& value);

	// Find an item in the tree
	// PRE: value is the value to find
	// POST: returns 1 if found or 0 if not found
	int find(const DType& value) const;

	// Remove all items from the tree
	// PRE: none
	// POST: all items are removed from the tree
	void purge(void);

	// Display the elements of the tree in order
	// PRE: list is the CListBox in which to put the items
	// POST: list holds the items in order
	void displayInOrder(CListBox& list) const;

	// Display the elements of the tree in pre order
	// PRE: list is the CListBox in which to put the items
	// POST: list holds the items in pre order
	void displayPreOrder(CListBox& list) const;

	// Display the elements of the tree in post order
	// PRE: list is the CListBox in which to put the items
	// POST: list holds the items in post order
	void displayPostOrder(CListBox& list) const;

private:

	// node for the tree
	struct Node {
		Node(const DType& value) : data(value) { right=left=0; }
		DType data;
		Node *right;
		Node *left;
	};

	Node *root;		// pointer to the root of the tree

	// Recursive function for removing an item from the tree
	// PRE: value is the item to remove, ptr points to the subtree
	// POST: removes node containing value if possible.
	//       returns 1 on success, or 0 on failure
	int remove(const DType& value, Node*& ptr);

	// Recursive function for purging the tree
	// PRE: ptr points to the subtree to purge
	// POST: the subtree of ptr is purged
	void resetTree(Node *ptr);

	// Recursive function for displaying the tree in order
	// PRE: list is the CListBox in which to display the subtree
	//      ptr points to the subtree
	// POST: list holds the items in the subtree pointed to by ptr
	void displayInOrder(CListBox& list, Node *ptr) const;

	// Recursive function for displaying the tree in pre order
	// PRE: list is the CListBox in which to display the subtree
	//      ptr points to the subtree
	// POST: list holds the items in the subtree pointed to by ptr
	void displayPreOrder(CListBox& list, Node *ptr) const;

	// Recursive function for displaying the tree in post order
	// PRE: list is the CListBOx in which to display the subtree
	// POST: list holds the items in the subtree pointed to by ptr
	void displayPostOrder(CListBox& list, Node *ptr) const;

};

#endif