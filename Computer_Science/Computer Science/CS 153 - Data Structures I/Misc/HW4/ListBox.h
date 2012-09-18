/****************************************************************************
*  Program #4    Programmers: Lance Callaway      Date: Feb 5, 2002
*                             Kieth Schaefer
*
*  This Program is used to enter, remove, and find CStrings in a 
*  list box of character arrays.  It also will tell if the array is
*  full or empty.
****************************************************************************/


#ifndef ListBox_H
#define ListBox_H
#include "stdafx.h"

class ListBox
{
// Function Prototypes
	public:
		ListBox ();
/* This is the default contructor
 *************************************************************************/
		
		CString find (CString);
/* This function returns a statement weather a given string is found 
in the List Box
PRE: CString from user
POST: Returns message of success or not
 *************************************************************************/
		
		CString remove (CString);
/* This function removes a given string from the list box
PRE: String from user
POST: Returns message of success or not
 *************************************************************************/
		
		CString insert (CString);
/* This function returns a statement weather a given string is found 
in the List Box
PRE: Number from user
POST: Returns message of success or not
 *************************************************************************/
		void display (CListBox &ListBox);
/* This function sets the data array to the ListBox variable
PRE: Class data array
POST: ListBox holds updated data array
 *************************************************************************/
		CString empty ();
/* This function returns a statement weather the ListBox is empty
PRE: Void
POST: Returns message of success or not
 *************************************************************************/
		CString full ();
/* This function returns a statement weather the ListBox is full
PRE: Void
POST: Returns message of success or not
 *************************************************************************/
		~ListBox ();
/* This is the deconstructor
 *************************************************************************/


//Private Member Variables
	private:
		char * data [10];	// Store "Bag" of information
		char * words;		// Converts CString into char array
		int size;			// Keeps track of ListBox size
		CString message;	// Returns messages about the function just used
};
#endif