// Bag.cpp: implementation of the CBag class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "prog5.h"
#include "Bag.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Create an empty bag
CBag::CBag() {
	size=0;
	current=elements=0;
	lastIndex=0;
}

// Copy constructor
CBag::CBag(const CBag& bag) {
	Node *p;		// index pointer
	Node *temp;		// pointer to a temporary node
	size=bag.size;
	elements=0;

	// Insert the elements into the new bag
	for(p=bag.elements;p;p=p->next) {
		temp=new Node;
		temp->value=p->value;
		if(elements) {
			temp->next=elements;
		}
		elements=temp;
	}
	lastIndex=0;	// Make sure operator[] knows the bag has changed
}

// Assignment
const CBag& CBag::operator =(const CBag& bag) {
	Node *p;		// index pointer
	Node *temp;		// pointer to a temporary node

	// Delete the old bag
	while(elements) {
		p=elements->next;
		delete elements;
		elements=p;
	}

	// Copy the contents of the new bag to this bag
	size=bag.size;
	elements=0;
	for(p=bag.elements;p;p=p->next) {
		temp=new Node;
		temp->value=p->value;
		if(elements) {
			temp->next=elements;
		}
		elements=temp;
	}
	lastIndex=0;	// Make sure operator[] knows the bag has changed
	return *this;
}

// Destroy the bag
CBag::~CBag() {
	Node *p;		// temporary node pointer

	// Delete all the nodes
	while(elements) {
		p=elements->next;
		delete elements;
		elements=p;
	}
}

// Insert a value to the bag
int CBag::insert(const int& value) {
	// Insert if the isn't full
	if(!isFull()) {
		Node *temp;
		temp=elements;
		elements=new Node;
		elements->value=value;
		elements->next=temp;
		++size;
		lastIndex=0;	// Make sure operator[] knows the bag has changed
		return 1;
	}
	return 0;
}

// Remove a value from the bag
int CBag::remove(const int& value) {
	Node *p;		// index node pointer
	Node *last;		// pointer to the last node accessed

	// Traverse the list, remove the first occurrence of value
	last=0;
	for(p=elements;p;p=p->next) {
		if(p->value==value) {
			if(last) {
				last->next=p->next;
			} else {
				elements=p->next;
			}
			delete p;
			--size;
			lastIndex=0;	// Make sure operator[] knows the bag has changed
			return 1;
		}
		last=p;
	}
	return 0;
}

// Check if a value is in the bag
int CBag::find(const int& value) const {
	Node *p;	// index node pointer

	// Traverse the list, return 1 if value was found
	for(p=elements;p;p=p->next) {
		if(p->value==value) {
			return 1;
		}
	}
	return 0;
}

// Is the bag empty?
int CBag::isEmpty(void) const {
	return size==0;
}

// Is the bag full?
int CBag::isFull(void) const {
	Node *p;	// Temporary node pointer
	try {
		p=new Node;
		if(p) {
			delete p;
			return 0;
		} else {
			return 1;
		}
	}
	catch(...) {
		return 1;
	}
}
			
// Returns the number of elements in the bag
int CBag::numberElements(void) const {
	return size;
}

// Returns the value of the element indexed by index
int CBag::operator [](const int& index) {

	// Restart if the bag has been modified or has yet to be initialized
	if(!lastIndex)
		current=elements;

	// Restart if the index is less than the index of the last lookup
	if(index<lastIndex) {
		current=elements;
		lastIndex=0;
	}

	// Search for the node with the correct index and return the result
	for(;lastIndex<index;lastIndex++) {
		if(!current || !current->next) return 0;
		current=current->next;
	}
	return current->value;
}


