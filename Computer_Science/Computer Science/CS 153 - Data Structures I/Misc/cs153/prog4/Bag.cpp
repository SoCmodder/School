// Bag.cpp: implementation of the CBag class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "prog4.h"
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
	max=CBAG_MIN_ALLOC;
	elements=new int[max];
}

// Copy constructor
CBag::CBag(const CBag& bag) {
	size=bag.size;
	max=bag.max;
	elements=new int[max];
	for(int x=0;x<size;elements[x]=bag.elements[x++]);
}

// Assignment
const CBag& CBag::operator =(const CBag& bag) {
	delete [] elements;
	size=bag.size;
	max=bag.max;
	elements=new int[max];
	for(int x=0;x<size;elements[x]=bag.elements[x++]);
	return *this;
}

// Destroy the bag
CBag::~CBag() {
	delete [] elements;
}

// Insert a value to the bag
int CBag::insert(const int& value) {
	// Insert if the isn't full
	if(!isFull()) {
		// Allocate more memory if necessary
		if(++size>=max) {
			int *temp;
			temp=new int[max+CBAG_BLOCK_SIZE];
			for(int x=0;x<max;temp[x]=elements[x++]);
			max+=CBAG_BLOCK_SIZE;
			delete [] elements;
			elements=temp;
		}
		elements[size-1]=value;
		return 1;
	}
	return 0;
}

// Remove a value from the bag
int CBag::remove(const int& value) {
	// Search for the element to remove
	for(int x=0;x<size;x++) {
		if(elements[x]==value) {
			// Remove the element/reduce array size
			--size;
			if(x<size) {
				elements[x]=elements[size];
			}
			// Free some memory if we have too much
			if(size<max-CBAG_BLOCK_SIZE && size>CBAG_MIN_ALLOC) {
				max-=CBAG_BLOCK_SIZE;
				int *temp=new int[max];
				for(x=0;x<max;temp[x]=elements[x++]);
				delete [] elements;
				elements=temp;
			}
			return 1;
		}
	}
	return 0;
}

// Check if a value is in the bag
int CBag::find(const int& value) const {
	for(int x=0;x<size;x++) {
		if(elements[x]==value) {
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
	return 0;	// Dynamic memory allocation is used
}
			
// Returns the number of elements in the bag
int CBag::numberElements(void) const {
	return size;
}

// Returns the value of the element indexed by index
int CBag::element(const int& index) const {
	if(size>index) {
		return elements[index];
	} else {
		return 0;	// This should never happen!
	}
}


