/****************************************************************************
*  Program #7    Programmers: Lance Callaway      Date: Feb 22, 2002
*                             Kieth Schaefer
*
*  This Program is used to enter, remove, and find Student data in a 
*  linked list of student nodes.  It also will tell if the linked list is
*  full or empty.  This assignment has moved the listbox display functionality 
*  to the Dlg.cpp.
****************************************************************************/
#ifndef STUDENT_H
#define STUDENT_H
#include "stdafx.h"
#include "Node.h"
class Student
{
// Function Prototypes
	public:
		Student ();
/* This is the default contructor - it sets the header/tail/current node 
pointers to NULL
 *************************************************************************/
		~Student ();
//-Lance		
		CString find (double t_GPA);
/* This function returns a statement weather a given student is found 
in the List Box
PRE: A linked list of student nodes has been created (including null list)
POST: No changes in Linked List, returns message
 *************************************************************************/
//Keith	
		CString remove (CString t_name);
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
		CString insert (CString t_name, int t_age, double t_GPA);
/* Inserts the data from the interface into the tail of the list
PRE: A linked list of student nodes has been created (including null list)
POST: The student has been added to linked list
 *************************************************************************/
		CString insertHead (CString t_name, int t_age, double t_GPA);
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
		CString GetNext ();
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