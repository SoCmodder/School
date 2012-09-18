#ifndef CHARNODE_H
#define CHARNODE_H
#include "stdafx.h"
#include "Node.h"

class CharNode: public Node
{
	public:
		CharNode ();
		~CharNode ()
		{}
		CharNode (char *);
		char * oper;
		virtual bool operator== (Node &arg);
};
#endif