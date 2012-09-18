#ifndef BST_H
#define BST_H

#include "stdafx.h"
#include "node.h"


class BST
{
	public:
		BST();
		void increase(Node *);

	private:
		Node * root;
};
#endif