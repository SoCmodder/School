// Data node for the Binary Search Tree
// Erin Pringle and Joe Wingbermuehle
// This is the implementation for CData, which inherits BNode

#include "stdafx.h"
#include "cdata.h"

// Default Constructor
// PRE: none
// POST: an empty CData object is created
CData::CData() {
	data="";
}

// Constructor with input
// PRE: str is the string to assign as the value
// POST: a new object with str is created
CData::CData(const char* str) {
	data=str;
}

// Destructor
// PRE: none
// POST: CData object is destroyed
CData::~CData() {
}

// == operator
// PRE: right is the CData to compare to
// POST: returns 1 if compare true, 0 if false
bool CData::operator ==(const BNode& right) const {
	return data==((CData*)(&right))->data;
}

// < operator
// PRE: right is the CData to compare to
// POST: returns 1 if compare true, 0 if false
bool CData::operator <(const BNode& right) const {
	return data<((CData*)(&right))->data;
}

// > operator
// PRE: right is the CData to compare to
// POST: returns 1 if compare true, 0 if false
bool CData::operator >(const BNode& right) const {
	return data>((CData*)(&right))->data;
}

// <= operator
// PRE: right is the CData to compare to
// POST: returns 1 if compare true, 0 if false
bool CData::operator <=(const BNode& right) const {
	return data<=((CData*)(&right))->data;
}

// >= operator
// PRE: right is the CData to compare to
// POST: returns 1 if compare true, 0 if false
bool CData::operator >=(const BNode& right) const {
	return data>=((CData*)(&right))->data;
}

// Display the node
// PRE: list is the CListBox in which to display the value
// POST: displays the value
void CData::Show(CListBox& list) const {
	list.AddString(data);
}

