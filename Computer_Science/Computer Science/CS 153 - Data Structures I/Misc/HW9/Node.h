#ifndef NODE_H
#define NODE_H
#include "stdafx.h"

class Node
{
	public:
		Node ();
		virtual ~Node ()
		{}
		Node * next;
		Node * previous;
		virtual bool operator == (Node &arg)=0;
};
#endif