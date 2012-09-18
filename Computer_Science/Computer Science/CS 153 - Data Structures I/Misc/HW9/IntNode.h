#ifndef INTNODE_H
#define INTNODE_H
#include "stdafx.h"
#include "Node.h"

class IntNode: public Node
{
	public:
		IntNode ();
		~IntNode ()
		{}
		IntNode (int);
		int num;
		virtual bool operator== (Node &arg);
};
#endif