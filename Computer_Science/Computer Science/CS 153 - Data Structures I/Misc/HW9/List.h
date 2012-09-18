/****************************************************************************
*  Program #9    Programmers: Lance Callaway      Date: March 20, 2002
*                             Kieth Schaefer
*
*	This program is designed to take a prefix equation and covert it to
*	postfix notation and then evaluate the expression
****************************************************************************/
#ifndef LIST_H
#define LIST_H
#include "stdafx.h"
#include "Node.h"
class List
{
// Function Prototypes
	public:
		List ();
/* This is the default contructor - it sets the header/tail/current node 
pointers to NULL
 *************************************************************************/
		~List ();
//-Lance		
		CString find (Node *);
/* This function returns a statement weather a given student is found 
in the List Box
PRE: A linked list of student nodes has been created (including null list)
POST: No changes in Linked List, returns message
 *************************************************************************/
//Keith	
		CString remove (Node *);
/* This function removes a given number from the list box
PRE: A linked list of student nodes has been created (including null list)
POST: Specified student is removed if he/she exists
 *************************************************************************/
		CString removeHead ();
/* This function removes the first node in the list
PRE: A linked list of student nodes has been created (including null list)
POST: First student is removed (if the list in not empty)
 *************************************************************************/
		CString removeTail ();
/* This function removes the last node in the list
PRE: A linked list of student nodes has been created (including null list)
POST: Last student is removed (if one exists)
 *************************************************************************/
//Lance		
		CString insert (Node *);
/* Inserts the data from the interface into the tail of the list
PRE: A linked list of student nodes has been created (including null list)
POST: The student has been added to linked list
 *************************************************************************/
		CString insertHead (Node *);
/* Inserts the data from the interface into the head of the list
PRE: A linked list of student nodes has been created (including null list)
POST: The student has been added to linked list
 *************************************************************************/
//Keith
		CString empty ();
/* This function returns a statement weather the ListBox is empty
PRE: A linked list of student nodes has been created (including null list)
POST: No changes in Linked List, returns message
 *************************************************************************/
//Lance
		CString full ();
/* This function returns a statement weather the ListBox is full
PRE: A linked list of student nodes has been created (including null list)
POST: No changes in Linked List, returns message
*************************************************************************/
		void Reset ();
/* This function resets the pointer
PRE: A linked list of student nodes has been created (including null list)
POST: The current pointer is set to the head pointer
*************************************************************************/
		bool EOL ();
/* Returns wether or not the current pointer is pointing to the last node
PRE: A linked list of student nodes has been created (including null list)
POST: None: Pointer does not change with this function
*************************************************************************/
		Node * GetNext ();
/* Moves the current pointer to the next node
PRE: The current pointer is not pointing at the last node
POST: The pointer has moved the the node that its current node's next field is pointing to
*************************************************************************/

//Private Member Variables
	private:
		Node * header;
		Node * tail;
		Node * current;
		CString message;
};
#endif