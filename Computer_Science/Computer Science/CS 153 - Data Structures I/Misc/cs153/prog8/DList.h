// DList.h: interface for the CDList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLIST_H__D09666FF_9960_11D4_ADD1_005056EC703B__INCLUDED_)
#define AFX_DLIST_H__D09666FF_9960_11D4_ADD1_005056EC703B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// Assignment 7 (Doubly Linked List Class)
// Erin Pringle and Joe Wingbermuehle
// This is the header for the CDList class

class CDList {
public:

	// Constructor
	// PRE: none
	// POST: a new (empty) CDList is created
	CDList();

	// Copy Constructor
	// PRE: right is the CDList to copy
	// POST: this is created as a copy of right
	//		 On an allocation error, this is empty
	CDList(const CDList& right);

	// Destructor
	// PRE: none
	// POST: the CDList is destroyed
	virtual ~CDList();

	// Purge the contents of the bag
	// PRE: none
	// POST: the contents of the bag are destroyed
	void purge(void);

	// Insert a string to the list
	// PRE: str is a pointer to the string to insert
	// POST: str is inserted to the list if possible
	//		 returns 1 on success, 0 on failure
	bool insertHead(const char* str);

	// Insert a string to the end of the list
	// PRE: str is a pointer to the string to insert
	// POST: str is inserted at the tail of the list if
	//       possible, returns 1 on success, 0 on failure
	bool insertTail(const char* str);

	//*** Insert a string before the current element
	// PRE: str is a pointer to the string to insert
	// POST: str is inserted before the current element if
	//       possible, returns 1 on success, 0 on failure
	bool insertBefore(const char* str);

	//*** Insert a string after the current element
	// PRE: str is a pointer to the string to insert
	// POST: str is inserted after the current element if
	//       possible, returns 1 on success, 0 on failure
	bool insertAfter(const char* str);

	// Remove an item from the list
	// PRE: str points to the string to remove
	// POST: removes the first instance of str from the
	//       list starting from the current position.
	//       returns 1 on success, 0 on failure
	bool remove(const char* str);

	// Remove the first string from the list
	// PRE: none
	// POST: removes the first element of the list if
	//       possible, returns string of the removed
	//       item or null on error
	CString removeHead(void);

	// Remove the last string from the list
	// PRE: none
	// POST: removes the last element of the list if
	//       possible, returns string of the removed
	//       item, or null on error
	CString removeTail(void);

	// Remove the current element from the list
	// PRE: none
	// POST: removes the current element of the list if
	//       possible, returns string of the removed
	//       item, or null on error
	CString removeCurrent(void);

	// Determine if a given string after the current position
	// PRE: str is the string to find
	// POST: returns 1 if the string is found, otherwise 0
	//       updates the current position
	bool find(const char* str);

	// Determine the number of elements in the list
	// PRE: none
	// POST: returns the number of elements in the list
	int numberElements(void);

	// Determine if the list is full
	// PRE: none
	// POST: returns 1 if full, 0 if not full
	bool full(void);

	// Determine if the list is empty
	// PRE: none
	// POST: returns 1 if empty, 0 if not empty
	bool empty(void);

	// Determines if the current position is at the end
	// PRE: none
	// POST: returns 1 if at the end, otherwise 0
	bool EOL(void);

	// Reset the current position to the first element
	// PRE: none
	// POST: the current position is reset
	void reset(void);

	// Retrieve the element at the current position
	// PRE: the list contains at least one element
	// POST: returns the element at the current position
	CString getCurrent(void);

	// Retrieve the element at the current position and advance
	// PRE: the list contains at least one element
	// POST: returns the current element and advances the position
	CString getNext(void);

	// Retrieve the element at the current position and go back
	// PRE: the list contains at least one element
	// POST: returns the current element and sets the position back
	CString getPrevious(void);

	// Retrieve the element at the start of the list
	// PRE: the list contains at least one element
	// POST: returns the element at the head of the list
	CString getHead(void);

	// Retrieve the element at the end of the list
	// PRE: the list contains at least one element
	// POST: returns the element at the tail of the list
	CString getTail(void);

	// Look up the data of the index given
	// PRE: index is an integer less than the value returned
	//		by numberElements and greater than 0
	// POST: returns the data of the index
	//		 NULL if bad index is out of range
	CString operator [](const int& index);

	// Assignment operator
	// PRE: right is the CDList to assign to this
	// POST: this is deleted and recreated as a copy of right
	//		 On an allocation error, this is empty
	CDList& operator=(const CDList& right);

	// Return the number of the current position
	// PRE: none
	// POST: returns the number (starting at 0) of the current position
	int currentNumber(void);

private:

	struct Node {

		// Constructor
		// PRE: none
		// POST: create a new (empty) Node
		Node() {
			data=0; next=prev=0;
		}

		// Constructor with input
		// PRE: str is a pointer to the string to insert
		//		ptr1 is a pointer to the previous Node
		//		ptr2 is a pointer to the next Node
		// POST: A new Node is created with the given string and pointers
		Node(const char* str, Node* ptr1, Node* ptr2) {
			data=new char[strlen(str)+1];
			strcpy(data,str);
			prev=ptr1; next=ptr2;
		}

		// Destructor
		// PRE: none
		// POST: the Node is destroyed
		~Node() {
			if(data) delete [] data;
		}

		Node *next;		// Pointer to the next Node
		Node *prev;		// Pointer to the previous Node
		char *data;		// Pointer to the Node data
	};

	Node *head;		// Pointer to the beginning of the list
	Node *tail;		// Pointer to the end of the list

	int count;		// The number of Nodes in the list

	int currentIndex;		// The number of the current location
	Node *currentPointer;	// A pointer to the current Node
};

#endif // !defined(AFX_DLIST_H__D09666FF_9960_11D4_ADD1_005056EC703B__INCLUDED_)
