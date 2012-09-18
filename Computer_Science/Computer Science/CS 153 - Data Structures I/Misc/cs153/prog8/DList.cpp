// DList.cpp: implementation of the CDList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// Assignment 8
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
		if(!insertHead(p->data)) {
			// Error, so reset and return
			purge();
			return;
		}
	}
}

// Assignment
CDList& CDList::operator =(const CDList& right) {
	Node *p;	// Index pointer

	purge();

	// Copy the items from right to this
	for(p=right.head;p;p=p->next) {
		if(!insertHead(p->data)) {
			// Error, so purge and return
			purge();
			return *this;
		}
	}
	return *this;
}

// Destructor
CDList::~CDList() {
	purge();
}

// Remove all items from the list
void CDList::purge(void) {
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
bool CDList::insertHead(const char *str) {
	try {
		// Insert the new Node if possible
		if(head)
			head=head->prev=new Node(str,0,head);
		else
			tail=head=new Node(str,0,head);
	}
	catch(...) {
		return 0;	// Return 0 on failure
	}

	++count;
	if(currentIndex) ++currentIndex;
	return 1;
}

// Append a string to the list
bool CDList::insertTail(const char *str) {
	try {
		// Append a new Node
		if(tail)
			tail=tail->next=new Node(str,tail,0);
		else
			head=tail=new Node(str,tail,0);
	}
	catch(...) {
		return 0;
	}
	if(!head) head=tail;
	++count;
	return 1;
}

// Remove a string from the list (start search at currentPointer)
bool CDList::remove(const char *str) {

	// Search for the string to remove
	while(currentPointer) {
		if(!strcmp(currentPointer->data,str)) {

			// Remove the string/update pointers
			if(currentPointer->prev)
				currentPointer->prev->next=currentPointer->next;
			else
				head=currentPointer->next;
			if(currentPointer->next)
				currentPointer->next->prev=currentPointer->prev;
			else
				tail=currentPointer->prev;
			delete currentPointer;
			--count;
			reset();		// Reset search
			return 1;
		}
		currentPointer=currentPointer->next;
		++currentIndex;
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

// Determine if we are at the end of the list
bool CDList::EOL(void) {
	return currentIndex>=count;
}

// Reset the current position to head
void CDList::reset(void) {
	currentPointer=head;
	currentIndex=0;
}

// Retrieve the element at the current position
CString CDList::getCurrent(void) {
	if(currentPointer) {
		return currentPointer->data;
	} else {
		return "";
	}
}

// Retrieve the element at the next position and advance
CString CDList::getNext(void) {
	if(currentPointer) {
		++currentIndex;
		if((currentPointer=currentPointer->next)) {
			return currentPointer->data;
		} else {
			return "";
		}
	} else {
		if((currentPointer=head)) {
			return currentPointer->data;
		} else {
			return "";
		}
	}
}

// Retrieve the element at the previous position and go back
CString CDList::getPrevious(void) {
	if(currentPointer) {
		--currentIndex;
		if((currentPointer=currentPointer->prev)) {
			return currentPointer->data;
		} else {
			return "";
		}
	} else {
		return "";
	}
}

// Retrieve the element at the start of the list
CString CDList::getHead(void) {
	if(head)
		return head->data;
	else
		return "";
}

// Retrieve the element at the end of the list
CString CDList::getTail(void) {
	if(tail)
		return tail->data;
	else 
		return "";
}

// Return the number of elements in the list
int CDList::numberElements(void) {
	return count;
}

// Determine if a string is in the list after the current pointer
bool CDList::find(const char *str) {

	// Search for a Node containing str
	while(currentPointer) {
		if(!strcmp(currentPointer->data,str)) {
			currentPointer=currentPointer->next;
			++currentIndex;
			return 1;
		}
		currentPointer=currentPointer->next;
		++currentIndex;
	}
	return 0;
}


// Return the value of the index given
CString CDList::operator [](const int& index) {

	// If the current pointer is null, restart search
	if(!currentPointer)
		currentIndex=0;

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
	return "";
}

// Return the number of the current position
int CDList::currentNumber(void) {
	return currentIndex;
}

//Inserts a new string before the current string
//PRE:  str is a pointer to the string to insert
//POST:  str is inserted before the current string in the list if possible
//		 returns 1 on success, 0 on failure
//		 currentPointer is set to the new Node
bool CDList::insertBefore(const char * str)
{
	if(!currentPointer) return 0;
	try 
	{
		//Adds the new Node before current
		if(currentPointer == NULL || currentPointer == head)
		{
			currentPointer->prev = new Node(str,0,head);
			head = currentPointer ->prev;
			currentPointer = head;
		}
		else
		{
			currentPointer->prev=new Node(str,currentPointer->prev,currentPointer);
			if(currentPointer->prev->prev)
				currentPointer->prev->prev->next=currentPointer->prev;
		}

	}
	catch(...) 
	{
		return 0;
	}

	count = count +1;
	++currentIndex;

	return 1;
}



//Inserts a new string after the current string
//PRE:  str is a pointer to the string to insert
//POST:  str is inserted after the current string in the list if possible
//		 returns 1 on success, 0 on failure
//		 currentPointer is set to the new Node
bool CDList::insertAfter(const char * str)
{
	if(!currentPointer) return 0;
	try 
	{
		//Adds the new Node after current
		if(currentPointer == NULL)
		{
			currentPointer->next = new Node(str,0,head);
			head = currentPointer ->prev;
			currentPointer = head;
		}
		else if (currentPointer == tail)
		{
			currentPointer->next = new Node(str,tail,0);
			tail = currentPointer ->next;
			currentPointer = tail;
		}
		else
		{
			currentPointer->next=new Node(str,currentPointer,currentPointer->next);
			if(currentPointer->next->next)
				currentPointer->next->next->prev=currentPointer->next;

		}

	}
	catch(...) 
	{
		return 0;
	}

	count = count + 1;

	return 1;


}


//The first Node in the list is removed and its string value returned.
//PRE:  The list is not empty.
//POST:  The first Node in the list has been removed and its data returned.
CString CDList::removeHead()
{
	Node *temp; //temporary pointer pointing to the same place as currentPointer
	CString data = ""; //data in the current node

	//removing head node
	if(head) {
		temp = head;
		data=temp->data;
		head = head->next;
		if(head)
			head->prev=0;
		delete temp;
		if(!head) tail=0;
		reset();
		--count;
	}

	return data;
}


//The last Node in the list is removed and its string value returned.
//PRE:  The list is not empty.
//POST:  The last Node in the list has been removed and its data returned.
CString CDList::removeTail()
{
	Node *temp; //temporary pointer pointing to the same place as currentPointer
	CString data = ""; //data in the current node

	//removing tail node
	if(tail) {
		temp=tail;
		tail=temp->prev;
		data=temp->data;
		if(tail)
			tail->next=0;
		delete temp;
		if(!tail) head=0;
		--count;
		reset();
	}
	return data;

}



//The current Node in the list is removed and its string value returned.
//PRE:  The list is not empty and a current Node exists.
//POST:  The current Node in the list has been removed and its data returned.
CString CDList::removeCurrent()
{
	Node *temp; //temporary pointer pointing to the same place as currentPointer
	CString data = ""; //data in the current node

	//removing current node
	if(currentPointer) {
		temp = currentPointer;
		if(currentPointer->prev)
			currentPointer->prev->next = currentPointer -> next;
		else
			head=currentPointer->next;
		if(currentPointer->next)
			currentPointer->next->prev = currentPointer ->prev;
		else
			tail=currentPointer->prev;
		data=temp->data;
		delete temp;
		reset();
		--count;
	}
	return data;

}