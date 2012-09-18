// DList.cpp: implementation of the CDList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DLinkedList.h"
#include "DList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// Assignment 6 (CDList implementation)
// Erin Pringle and Joe Wingbermuehle
// This is the implementation for the CDList class

// Constructor
CDList::CDList() {
	currentPointer=head=tail=0;
	currentIndex=count=0;
}

// Copy constructor
CDList::CDList(const CDList& right) {
	Node *p;	// Index pointer

	currentPointer=head=tail=0;
	currentIndex=count=0;

	// Copy the items from right to this
	for(p=right.head;p;p=p->next) {
		if(!insert(p->data)) {
			// Error, so reset and return
			reset();
			return;
		}
	}
}

// Assignment
CDList& CDList::operator =(const CDList& right) {
	Node *p;	// Index pointer

	reset();

	// Copy the items from right to this
	for(p=right.head;p;p=p->next) {
		if(!insert(p->data)) {
			// Error, so reset and return
			reset();
			return *this;
		}
	}
	return *this;
}

// Destructor
CDList::~CDList() {
	reset();
}

// Remove all items from the list
void CDList::reset(void) {
	Node *p;	// Temporary pointer

	// Delete all the Nodes
	while(head) {
		p=head->next;
		delete head;
		head=p;
	}
	tail=0;
	currentIndex=count=0;
}

// Insert a string to the list
bool CDList::insert(const char *str) {
	try {
		// Insert the new Node if possible
		if(head)
			head=head->prev=new Node(str,0,head);
		else
			head=new Node(str,0,head);
	}
	catch(...) {
		return 0;	// Return 0 on failure
	}

	if(!tail) tail=head;
	++count;
	currentIndex=0;		// Reset search
	return 1;
}

// Append a string to the list
bool CDList::append(const char *str) {
	try {
		// Append a new Node
		if(tail)
			tail=tail->next=new Node(str,tail,0);
		else
			tail=new Node(str,tail,0);
	}
	catch(...) {
		return 0;
	}
	if(!head) head=tail;
	++count;
	currentIndex=0;		// Reset search
	return 1;
}

// Remove a string from the list
bool CDList::remove(const char *str) {
	Node *p;	// Index pointer

	// Search for the string to remove
	for(p=head;p;p=p->next) {
		if(!strcmp(p->data,str)) {
			// Remove the string/update pointers
			if(p->prev)
				p->prev->next=p->next;
			else
				head=p->next;
			if(p->next)
				p->next->prev=p->prev;
			else
				tail=p->prev;
			delete p;
			--count;
			currentIndex=0;		// Reset search
			return 1;
		}
	}
	return 0;
}

// Determine if the list is full
bool CDList::full(void) {
	Node *temp;		// Temporay pointer

	// Check if we can allocate a new Node
	try {
		temp=new Node;
		temp->data=new char[2];
		delete temp;
		return 0;
	}
	catch(...) {
		return 1;		// List is full if this fails
	}
}

// Determine if the list is empty
bool CDList::empty(void) {
	return count==0;
}

// Return the number of elements in the list
int CDList::numberElements(void) {
	return count;
}

// Determine if a string is in the list
bool CDList::find(const char *str) {
	Node *p;	// Index pointer

	// Search for a Node containing str
	for(p=head;p;p=p->next) {
		if(!strcmp(p->data,str)) {
			return 1;
		}
	}
	return 0;
}

// Return the (const)char* of the index given
const char* CDList::operator [](const int& index) {

	// If !currentIndex, currentPointer must be head
	if(!currentIndex)
		currentPointer=head;

	// Move to the index if it exists
	while(currentPointer) {
		if(currentIndex==index)
			return currentPointer->data;

		// Move forward if currentIndex is too small
		if(currentIndex<index) {
			currentPointer=currentPointer->next;
			++currentIndex;
		}

		// Move backward if currentIndex is too big
		if(currentIndex>index) {
			currentPointer=currentPointer->prev;
			--currentIndex;
		}
	}

	// Opps, invalid index (this should not happen!)
	currentIndex=0;
	return 0;
}
