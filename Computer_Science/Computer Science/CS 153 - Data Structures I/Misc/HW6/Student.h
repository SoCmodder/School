/****************************************************************************
*  Program #6    Programmers: Lance Callaway      Date: Feb 18, 2002
*                             Kieth Schaefer
*
*  This Program is used to enter, remove, and find Student data in a 
*  linked list of student nodes.  It also will tell if the linked list is
*  full or empty.
****************************************************************************/
#ifndef Student_H
#define Student_H
#include "stdafx.h"

class Student
{
// Function Prototypes
	public:
		Student ();
/* This is the default contructor - it sets the header/tail/current node 
pointers to NULL
 *************************************************************************/
//-Lance		
		CString find (CString t_name, int t_age, double t_GPA);
/* This function returns a statement weather a given student is found 
in the List Box
PRE: A linked list of student nodes has been created (including null list)
POST: No changes in Linked List, returns message
 *************************************************************************/
//Keith	
		CString remove (CString t_name, int t_age, double t_GPA);
/* This function removes a given number from the list box
PRE: A linked list of student nodes has been created (including null list)
POST: Specified student is removed if he/she exists
 *************************************************************************/
//Lance		
		CString insert (CString t_name, int t_age, double t_GPA);
/* This function returns a statement weather a given number is found 
in the List Box
PRE: A linked list of student nodes has been created (including null list)
POST: The student has been added to linked list
 *************************************************************************/
// Both
		void display (CListBox &ListBox);
/* This function sets the data array to the ListBox variable
PRE: A linked list of student nodes has been created (including null list)
POST: ListBox holds any updated data performed by insert/remove
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
//Keith - Nodes


//Private Member Variables
	private:
		node * header;
		node * tail;
		node * current;
		CString message;
};
#endif