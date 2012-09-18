

#include "Node.h"


Node::node()
{
	Node * arg;
	arg = new Node;
	
	arg.name = NULL;
	arg.age = 0;
	arg.GPA = 0.0;
	arg.next = NULL;
	arg.prev = NULL;
}

Node::node(CString,int,double)
{
	name = t_name;
	age = t_age;
	GPA = t_GPA;
	next = NULL;
	prev = NULL;
}