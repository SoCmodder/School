/*
File: tree.cpp
Author: Brent Powers
Date: 4-14-05
Description: Function definitions for node struct and bst class
*/#include "stdafx.h"
#include "tree.h"

;using namespace std;

/*
Function: Node()
Description: Default constructor for Node struct
Precondition:None
Postcondition: data set to zero; Left and Right child pointer
				set to zero
*/
Node::Node()
{
	data=0;
	LC=NULL;//left child
	RC=NULL;//right child
}

/*
Function: BST()
Description: Default Constructor for the BST class
Precondition: None
Postcondition: Sets the root_ptr to NULL
*/
BST::BST()
{
	root_ptr=NULL;//root pointer
}

/*
Function:~BST()
Description: Default destructor for the BST class
Precondition: Tree is properly linked
Postcondition: All the nodes in the tree are returned to memory
				through recursive functions
*/
BST::~BST()
{
	destructor_helper(root_ptr);//recursive deleter function
}

/*
Function: destructor_helper(Node *root)
Description: Recursive call function to delete all nodes in the 
			binnary tree 
Precondition: Tree is proberly linked
Postcondition: All nodes are deleted and returned to memory
*/
void BST::destructor_helper(Node * root)
{
	if (root == NULL)//if pointer is null
		return;
	destructor_helper(root->LC);//go to left child
	destructor_helper(root->RC);//go to right child
	delete root;//delete that part of memory
	return;
}

/*
Function: Find(const int target)
Description: Find call function to locate value in th BST
Precondition: target is a good value
Postcondition: return TRUE if value is found in the tree
				return FALSE if value is not found in tree
*/
bool BST::Find(const int target)
{
    return find_helper(target,root_ptr);//recursive search

}

/*
Function: find_helper(int target, Node* r)
Description: The recursive function to locate value in tree
Precondition: Propersly linked tree and valid pointer
Postcondition: True if value found in tree
				false if value not found in tree
*/
bool BST::find_helper(int target, Node* r)
{
	if(r==NULL)//node is null
		return false;
	else
	{
		if(r->data==target)//if target is found
			return true;
		else if(r->data<target)//if target is greater than  node
			return find_helper(target, r->RC);//move to right child
		else if(r->data>target)//if target is less than node
			return find_helper(target, r->LC);//move to left child
	}
}

/*
Function: insert(const int input)
Description: inserts a node into the correct spot on the BST
Precondition: input is valid
Postcondition: Node is correctly placed in tree
*/
void BST::insert(const int input)
{
	Node* temp = root_ptr;//temperary node

	if (root_ptr == NULL)//no nodes in tree
	{
		root_ptr = new Node;//make new node
		root_ptr->data = input;
		return;
	}
	
	while (temp != NULL)
	{
		if (input < temp->data)//if input is less than node
		{		
			if (temp->LC == NULL)//go to right child
			{
				temp->LC = new Node;
				temp->LC->data =  input;
				return;
			}
			else
				temp = temp->LC;// go to right child
		}
		else
		{
			if (temp->RC == NULL)//if input is greater than node
			{
				temp->RC = new Node;//make new node
				temp->RC->data = input;
			
				return;
			}
			else
				temp = temp->RC;//go to right child
		}
	}
}

/*
Function: isEmpty()
Description: Checks to see if the BST is empty or not
Precondition: none
Postcondition: True if BST is empty
				False if BST is not empty
*/
bool BST::isEmpty()
{
	if(root_ptr==NULL)//no root node
		return true;
	else
		return false;
}

/*
Function: DisplayHelper(CListBox &output, Node *leaf)
Description: Recursive display function inorder
Precondition: valid CListBox and good node
Postcondition: Adds all the nodes in the BST to the outbox
				in the inorder traversal
*/
void BST::DisplayHelper(CListBox &output, Node *leaf)
{
	char temp[20]="";//temperary char
	if (leaf == NULL)//if nothing there
		return;
	DisplayHelper(output, leaf->LC);//print left child
	_itoa(leaf->data,temp,10);
	strncat(temp,", ",2);
	output.AddString(temp);//print node
	DisplayHelper(output, leaf->RC);//print right child
	return;
}

/*
Function: Display(CListBox &output)
Description: Call function for display
Precondition:Valid CListBox passed
Postcondition: All nodes outputted in order traversal
*/
void BST::Display(CListBox &output)
{
	output.ResetContent();//reset box
	DisplayHelper(output,root_ptr);//recursive call
	return;
}
