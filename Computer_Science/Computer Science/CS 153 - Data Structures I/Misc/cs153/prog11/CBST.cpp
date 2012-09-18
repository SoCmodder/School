//CBST.cpp
//Erin Pringle and Joe Wingbermuehle
//Member functions of the CBST class.

#include "stdafx.h"
#include "CBST.h"

//Constructor
//PRE:  none
//POST:  A new empty tree is created.
CBST::CBST()
{
	root=0;
}

//Destructor
//PRE:  root is the root pointer of a binary tree
//POST:  The tree is deleted and the root set to NULL.
CBST::~CBST()
{
	HelpDestruct(root);
}
	
//Inserts an integer into the tree
//PRE:  arg is an integer
//POST:  arg is inserted into the appropriate place in the tree
bool CBST::Insert(BNode *arg)
{
	BNode *current; //current node pointer

	current=root;
	
	//if no numbers have been inserted into the tree yet, arg becomes the first
	if(current == NULL)
	{
		root=arg;
		return true;
	}

	//inserting arg in correct place and returning true after it's inserted
	while (current != NULL)
	{
		if (*arg < *current)
		{
			if (current->left == NULL)
			{
				current->left = arg;
				return true;
			}

			current = current->left;
		}
		else
		{
			if (current->right == NULL)
			{
				current->right = arg;
				return true;
			}

			current = current->right;
		}
	}
	return false;
}
	
//Finds an integer in the tree
//PRE:  arg is an integer
//POST:  Returns true if arg is found in the tree, false if 
//       it is not found.
bool CBST::Find(BNode *arg) const
{
	BNode *current; //current BNode pointer

	current = root;

	//if arg is equal to the data in the current BNode,
	//true is returned.  Otherwise current is incremented to the
	//next appropriate BNode.
	while (current != NULL)
	{
		if (*current == *arg)
		{
			return true;
		}
		else if (*current > *arg)
		{
			current = current->left;
		}
		else if (*current < *arg)
		{
			current = current->right;
		}
	}

	//False is returned if arg was not found in the tree.
	return false;
}
	
//Displays the tree in order
//PRE: box is the CListBox in which to display the tree
//POST:  The tree is displayed in the CListBox box in order.
void CBST::DisplayInOrder(CListBox &box)
{
	//Displaying the tree
	DisplayInOrder(box,root);
}

//Helper function to the display function
//PRE: box is the CListBox in which to display the subtree
//      current points to the subtree
//POST:  The tree is displayed in the list box in order.
void CBST::DisplayInOrder(CListBox &box, BNode *current)
{
	if (current == NULL)
		return;
	else
	{
		DisplayInOrder(box, current->left);
		current->Show(box);
		DisplayInOrder(box, current->right);
	}
}

// Display the elements of the tree in pre order
// PRE: box is the CListBox in which to put the items
// POST: box holds the items in order
void CBST::DisplayPreOrder(CListBox& box) {
	DisplayPreOrder(box,root);
}

// Recursive function for displaying the tree in pre order
// PRE: list is the CListBox in which to display the subtree
//      ptr points to the subtree
// POST: list holds the items in the subtree pointed to by ptr
void CBST::DisplayPreOrder(CListBox& list, BNode *ptr) {
	if(ptr) {
		DisplayPreOrder(list,ptr->left);
		DisplayPreOrder(list,ptr->right);
		ptr->Show(list);
	}
}

// Display the elements of the tree in post order
// PRE: list is the CListBox in which to put the items
// POST: list holds the items in order
void CBST::DisplayPostOrder(CListBox& list) {
	DisplayPostOrder(list,root);
}

// Recursive function for displaying the tree in post order
// PRE: list is the CListBox in which to display the subtree
//      ptr points to the subtree
// POST: list holds the items in the subtree pointed to by ptr
void CBST::DisplayPostOrder(CListBox& list, BNode *ptr) {
	if(ptr) {
		ptr->Show(list);
		DisplayPostOrder(list,ptr->left);
		DisplayPostOrder(list,ptr->right);
	}
}

//Helper function to the destructor
//PRE:  root is the root pointer of a binary tree
//POST:  The tree is deleted and root set to NULL.
void CBST::HelpDestruct(BNode *current)
{
	//deleting tree using recursion
	if (current != NULL)
	{
		HelpDestruct(current->left);
		HelpDestruct(current->right);
		delete current;
		current = NULL;
	}
}

// Remove a BNode from the tree
// PRE: value is the item to remove
// POST: removes value from the tree (if possible), returns 1 if found
//       0 if not found
bool CBST::Remove(BNode *value) {
	return Remove(value,root);
}

// Remove a BNode from a subtree
// PRE: value is the value of the BNode to delete, ptr points to the subtree
// POST: the BNode is removed from the tree if possible
//       returns 1 on success, 0 on failure
bool CBST::Remove(BNode *value, BNode*& ptr) {
	BNode **temp;	// a pointer to the pointer to a BNode for deletion
	BNode *tp;

	// base case
	if(!ptr) return 0;

	// remove BNode on left subtree if value<current BNode
	if(*ptr>*value) {
		return Remove(value,ptr->left);

	// remove BNode on right subtree if value>current BNode
	} else if(*ptr<*value) {
		return Remove(value,ptr->right);

	} else {	// value==ptr->data

		if(ptr->right) {
			// get a reference to the pointer to the leftmost right BNode
			for(temp=&ptr->right;(*temp)->left;temp=&(*temp)->left);

			tp=ptr;
			ptr=*temp;
			*temp=(*temp)->right;
			ptr->right=tp->right;
			ptr->left=tp->left;
			delete tp;

		} else if(ptr->left) {
			// get a reference to the pointer to the rightmost left BNode
			for(temp=&ptr->left;(*temp)->right;temp=&(*temp)->right);

			tp=ptr;
			ptr=*temp;
			*temp=(*temp)->left;
			ptr->right=tp->right;
			ptr->left=tp->left;
			delete tp;

		} else {	// a leaf
			delete ptr;
			ptr=0;
		}

		return 1;
	}
}

// Remove all items from the tree
// PRE: none
// POST: all items are removed from the tree
void CBST::Purge(void) {
	HelpDestruct(root);
	root=0;
}
