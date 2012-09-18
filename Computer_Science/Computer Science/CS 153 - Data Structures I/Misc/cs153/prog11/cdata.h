// Data node for the Binary Search Tree
// Erin Pringle and Joe Wingbermuehle
// This is the header for CData, which inherits BNode

#ifndef CDATA_H
#define CDATA_H

#include "CBST.h"

// A node to contain a CString
class CData : BNode {
public:

	// Default Constructor
	// PRE: none
	// POST: an empty CData object is created
	CData();

	// Constructor with input
	// PRE: str is the string to assign as the value
	// POST: a new object with str is created
	CData(const char* str);

	// Destructor
	// PRE: none
	// POST: CData object is destroyed
	~CData();

	// CData* to BNode* conversion operator
	// PRE: none
	// POST: returns a BNode* to a CData object
	operator BNode*() { return this; };

	// Comparison functions
	// PRE: right is the BNode to compare to
	// POST: returns 1 if compare true, 0 if false;
	bool operator ==(const BNode& right) const;
	bool operator <(const BNode& right) const;
	bool operator >(const BNode& right) const;
	bool operator <=(const BNode& right) const;
	bool operator >=(const BNode& right) const;

	// Display the node
	// PRE: list is the CListBox in which to display the value
	// POST: displays the value
	void Show(CListBox& list) const;

private:

	CString data;		// value for the node
};

#endif