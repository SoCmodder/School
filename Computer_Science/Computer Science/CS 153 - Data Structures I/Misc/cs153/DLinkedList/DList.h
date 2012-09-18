// DList.h: interface for the CDList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLIST_H__9D94FB3E_90C8_11D4_ADCA_005056EC703B__INCLUDED_)
#define AFX_DLIST_H__9D94FB3E_90C8_11D4_ADCA_005056EC703B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Assignment 6 (Doubly Linked List Class)
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

	// Delete the contents of the bag
	// PRE: none
	// POST: the contents of the bag are destroyed
	void reset(void);

	// Insert a string to the list
	// PRE: str is a pointer to the string to insert
	// POST: str is inserted to the list if possible
	//		 returns 1 on success, 0 on failure
	bool insert(const char* str);

	// Append a string to the list
	// PRE: str is a pointer to the string to append
	// POST: str is appened to the list if possible
	//		 returns 1 on success, 0 on failure
	bool append(const char* str);

	// Remove a string from the list
	// PRE: str is the string to remove
	// POST: the first instance of str is removed if possible
	//		 returns 1 on success, 0 on failure
	bool remove(const char* str);

	// Determine if a given string is in the list
	// PRE: str is the string to find
	// POST: returns 1 if the string is found, otherwise 0
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

	// Look up the (const)char* of the index given
	// PRE: index is an integer less than the value returned
	//		by numberElements and greater than 0
	// POST: returns the (const)char* of the index
	//		 NULL if bad index is out of range
	const char* operator [](const int& index);

	// Assignment operator
	// PRE: right is the CDList to assign to this
	// POST: this is deleted and recreated as a copy of right
	//		 On an allocation error, this is empty
	CDList& operator=(const CDList& right);

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

#endif // !defined(AFX_DLIST_H__9D94FB3E_90C8_11D4_ADCA_005056EC703B__INCLUDED_)
