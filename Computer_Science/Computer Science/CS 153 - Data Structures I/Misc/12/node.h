#ifndef NODE_H
#define NODE_H
#include "stdafx.h"

class Node
{
	public:
		Node ();
		CString data;
		Node * LC;
		Node * RC;
};
#endif