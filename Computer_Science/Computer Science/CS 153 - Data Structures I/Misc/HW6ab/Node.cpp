#include "stdafx.h"
#include "Node.h"



Node::Node ()
{
	next = NULL;
	previous = NULL;
}


Node::Node (CString Name, int Age, double GPa)
{
	next = NULL;
	previous = NULL;
	name = Name;
	age = Age;
	GPA = GPa;
}
