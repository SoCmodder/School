#ifndef NODE_H
#define NODE_H
#include "stdafx.h"

class Node
{
	public:
		Node ();
		Node (CString, int, double);
		Node * next;
		Node * previous;
		CString name;
		int age;
		double GPA;
};
#endif