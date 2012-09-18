/*
File: tree.h
Author: Brent Powers
Date: 4-14-05
Description: Class and Struct definitions for Node struct and BST
*/#ifndef TREE_H
#define TREE_H

struct Node//the struct for each node of the tree
{
	Node();//constructor
	int data;//data that is in each of the nodes
    Node* LC;//pointer to the left child of the node
	Node* RC;//pointer to the right child of the node
};



class BST//class used for handeling all functions of the tree
{
public:
	BST();//constructor
	~BST();//destructor
	void insert(const int input);//function to insert a node into the tree
	bool Find(const int target);//Find function for tree
	bool isEmpty();//Function to find if the tree is empty or not
	void Display(CListBox &output);//Display call function for the tree
private:
	void DisplayHelper(CListBox &output, Node* leaf);//recursive display
	Node* root_ptr;//root pointer for ttree
	bool find_helper(int target, Node* r);//recursive help function
	void BST::destructor_helper(Node * root);//recursive destructor

}


#endif