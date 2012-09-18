#include "stdafx.h"
#include "BST.H"

BST::BST()
{
	root = NULL;
	cur = root;
}

void BST::increase(Node * root)
{
	if(root == NULL)
	{
		return;
	}

	root ->data++;

//	if(root ->LC != NULL)
		increase(root ->LC);
//	if(root ->RC != NULL)
		increase(root ->RC);
	return;
}

int BST::sum_all(Node * root)
{
	int total;

	if (root == NULL)
	{
		return 0;
	}

	total = sum_all(root -> LC);
	total = sum_all(root -> RC);
	total += root -> data;

	return total;
}


size_t BST::many_nodes(Node * root)
{
	int num;

	if(root == NULL)
	{
		return 0;
	}

	num++;
	many_nodes(root->LC);
	many_nodes(root->RC);

	return num;
}