
// Program 10: Binary tree demonstration (implementation for CTree)
// Erin Pringle and Joe Wingbermuehle
// This is a program to demonstrate a binary tree

#include "stdafx.h"
#include "ctree.h"

// Constructor
// PRE: none
// POST: creates a new, empty tree
CTree::CTree() {
	root=0;
}

// Destructor
// PRE: none
// POST: deletes all nodes from the tree
CTree::~CTree() {
	resetTree(root);
}

// Display the elements of the tree in order
// PRE: list is the CListBox in which to put the items
// POST: list holds the items in order
void CTree::displayInOrder(CListBox& list) const {
	list.ResetContent();
	displayInOrder(list,root);
}

// Recursive function for displaying the tree in order
// PRE: list is the CListBox in which to display the subtree
//      ptr points to the subtree
// POST: list holds the items in the subtree pointed to by ptr
void CTree::displayInOrder(CListBox& list, Node *ptr) const {
	char str[20];		// string for int to string conversion
	if(ptr) {
		displayInOrder(list,ptr->left);
		itoa(ptr->data,str,10);
		list.AddString(str);
		displayInOrder(list,ptr->right);
	}
}

// Display the elements of the tree in pre order
// PRE: list is the CListBox in which to put the items
// POST: list holds the items in order
void CTree::displayPreOrder(CListBox& list) const {
	list.ResetContent();
	displayPreOrder(list,root);
}

// Recursive function for displaying the tree in pre order
// PRE: list is the CListBox in which to display the subtree
//      ptr points to the subtree
// POST: list holds the items in the subtree pointed to by ptr
void CTree::displayPreOrder(CListBox& list, Node *ptr) const {
	char str[20];	// string for int to string conversion
	if(ptr) {
		displayPreOrder(list,ptr->left);
		displayPreOrder(list,ptr->right);
		itoa(ptr->data,str,10);
		list.AddString(str);
	}
}

// Display the elements of the tree in post order
// PRE: list is the CListBox in which to put the items
// POST: list holds the items in order
void CTree::displayPostOrder(CListBox& list) const {
	list.ResetContent();
	displayPostOrder(list,root);
}

// Recursive function for displaying the tree in post order
// PRE: list is the CListBox in which to display the subtree
//      ptr points to the subtree
// POST: list holds the items in the subtree pointed to by ptr
void CTree::displayPostOrder(CListBox& list, Node *ptr) const {
	char str[20];	// string for int to string conversion
	if(ptr) {
		itoa(ptr->data,str,10);
		list.AddString(str);
		displayPostOrder(list,ptr->left);
		displayPostOrder(list,ptr->right);
	}
}

// Insert an item to the tree
// PRE: value is the item to insert
// POST: inserts the item, returns 1 on success, 0 on failure
int CTree::insert(const DType& value) {
	Node *p=root;		// pointer to current subtree
	Node *temp;			// temporary Node* for insertion

	// Create new node or return 0 for failure
	try {
		temp=new Node(value);
	}
	catch(...) {
		return 0;
	}

	if(root) {

		// Traverse the tree to the point of insertion & insert
		for(;;) {
			if(value<p->data) {

				// If we hit a leaf, insert, otherwise continue
				if(!p->left) {
					p->left=temp;
					break;
				} else {
					p=p->left;
				}
			} else {

				// If we hit a leaf, insert, otherwise continue
				if(!p->right) {
					p->right=temp;
					break;
				} else {
					p=p->right;
				}
			}
		}
	} else {
		root=temp;
	}
	return 1;
}

// Remove a node from the tree
// PRE: value is the item to remove
// POST: removes value from the tree (if possible), returns 1 if found
//       0 if not found
int CTree::remove(const DType& value) {
	return remove(value,root);
}

// Remove a node from a subtree
// PRE: value is the value of the node to delete, ptr points to the subtree
// POST: the node is removed from the tree if possible
//       returns 1 on success, 0 on failure
int CTree::remove(const DType& value, Node*& ptr) {
	Node **temp;	// a pointer to the pointer to a node for deletion

	// base case
	if(!ptr) return 0;

	// remove node on left subtree if value<current node
	if(value<ptr->data) {
		return remove(value,ptr->left);

	// remove node on right subtree if value>current node
	} else if(value>ptr->data) {
		return remove(value,ptr->right);

	} else {	// value==ptr->data

		if(ptr->right) {
			// get a reference to the pointer to the leftmost right node
			for(temp=&ptr->right;(*temp)->left;temp=&(*temp)->left);
			ptr->data=(*temp)->data;
			remove((*temp)->data,*temp);
		} else if(ptr->left) {
			// get a reference to the pointer to the rightmost left node
			for(temp=&ptr->left;(*temp)->right;temp=&(*temp)->right);
			ptr->data=(*temp)->data;
			remove((*temp)->data,*temp);
		} else {	// a leaf
			delete ptr;
			ptr=0;
		}

		return 1;
	}
}

// Find an item in the tree
// PRE: value is the value to find
// POST: returns 1 if found or 0 if not found
int CTree::find(const DType& value) const {
	Node *p=root;	// pointer to current subtree

	// traverse the tree
	while(p) {
		if(value<p->data) {
			p=p->left;
		} else if(value>p->data) {
			p=p->right;
		} else {	// value==p->data
			return 1;
		}
	}

	return 0;
}

// Remove all items from the tree
// PRE: none
// POST: all items are removed from the tree
void CTree::purge(void) {
	resetTree(root);
	root=0;
}

// Recursive function for purging the tree
// PRE: ptr points to the subtree to purge
// POST: the subtree of ptr is purged
void CTree::resetTree(Node *ptr) {
	if(ptr) {
		resetTree(ptr->right);
		resetTree(ptr->left);
		delete ptr;
	}
}

