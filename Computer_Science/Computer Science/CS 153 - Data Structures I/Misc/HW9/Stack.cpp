#include "stdafx.h"
#include "Stack.h"


void Stack::push (Node * newEntry)
{
	CString temp;
	temp = insertHead (newEntry);
}




Node * Stack::pop ()
{
	Node * temp;
	CString temp2;
	Reset ();
	temp = GetNext ();
	temp2 = removeHead ();
	return temp;
}




Node * Stack::top ()
{
	Node * temp;
	Reset ();
	temp = GetNext ();
	return temp;
}

	

