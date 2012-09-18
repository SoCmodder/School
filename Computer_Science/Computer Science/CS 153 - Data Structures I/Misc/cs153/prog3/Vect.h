// Vect.h: interface for the CVect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECT_H__528C454D_842D_11D4_A46C_006097D2E7B9__INCLUDED_)
#define AFX_VECT_H__528C454D_842D_11D4_A46C_006097D2E7B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Assignment 3
// Erin Pringle and Joe Wingbermuehle
// Vector class, allows one to create vectors from CStrings and use +,-,* etc.

// These would be in the CVect class if the VC++ compiler adhered to C++ standards....
// Bjarne Stroustrup "The C++ Programming Language" Section 10.4.6.2 explicitly states that
// we can have static const int as a class member
const int MAX_NUMBER=100;		// Max number of items in CVect
const int MAX_LENGTH=256;		// Max lenght of a vector string

class CVect  
{
public:
	typedef int VType;		// Type of each vector element
	// Default Constructor
	// PRE: none
	// POST: creates an empty CVect
	CVect();

	// Constructor that converts a CString to a CVect
	// PRE: the input is a list of signed ints separated by commas, spaces etc. (garbage is ignored)
	// POST: a CVect is created with a list of signed ints from the CString
	CVect(const CString&);

	// Destructor
	// PRE: none
	// POST: nothing really, but the object is destroyed
	virtual ~CVect();

	// Take two CVects and return their sum
	// PRE: the calling CVect and the input CVect should be the same size for good output
	// POST: returns the sum if possible, otherwise returns zero
	CVect operator +(const CVect& input) const;

	// Return the result after the input is subtracted from the calling CVect
	// PRE: both the calling CVect and the input CVect should be the same size for good output
	// POST: returns the difference if possible, otherwise returns zero
	CVect operator -(const CVect& input) const;

	// Return the dot product of calling CVect and the input CVect
	// PRE: both the calling CVect and the input CVect should be the same size for good output
	// POST: returns the dot product if possible, otherwise returns zero
	CVect operator *(const CVect& input) const;

	// Convert a CString list of signed ints separated by commas, spaces etc. to a CVect
	// PRE: the input is a list of signed ints (garbage is ignored)
	// POST: the calling CVect will contain the new vector created from the CString
	CVect operator =(const CString& input);

	// Create a string (char*) to represent the CVect
	// PRE: none
	// POST: creates a char* to represent the CVect
	char *toString(void) const;

	// Return the number of values in the vector
	// PRE: none
	// POST: returns the number of values in the vector
	int length(void) const;

private:
	int valueCount;				// Number of items in the CVect
	VType values[MAX_NUMBER];	// The actual vector elements
};

#endif // !defined(AFX_VECT_H__528C454D_842D_11D4_A46C_006097D2E7B9__INCLUDED_)
