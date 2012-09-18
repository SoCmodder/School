// Bag.h: interface for the CBag class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BAG_H__1EC94D55_85BF_11D4_A46D_006097D2E7B9__INCLUDED_)
#define AFX_BAG_H__1EC94D55_85BF_11D4_A46D_006097D2E7B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// This is a "bag" class, used to hold ints

const int CBAG_MIN_ALLOC=2;		// The minimum number of elements to allocate
const int CBAG_BLOCK_SIZE=4;	// Number of elements to allocate when
								// we run out

class CBag {
public:

	// Default constructor
	// PRE: None
	// POST: An empty CBag is created
	CBag();

	// Copy constructor
	// PRE: Input is an existing CBag
	// POST: A CBag is created identical to the inputed CBag
	CBag(const CBag& bag);

	// Destructor
	// PRE: None
	// POST: The CBag is destroyed
	virtual ~CBag();

	// Assignment
	// PRE: Input is new contents for this CBag
	// POST: The contents of the input are copied to this CBag and the old
	// contents are destroyed
	const CBag& operator =(const CBag& bag);

	// Insert an item to the CBag
	// PRE: value is the int to insert
	// POST: Add value to the CBag if possible, return 1 on success, 0 on failure
	int insert(const int& value);

	// Remove an item from the CBag
	// PRE: value is the int to remove
	// POST: The first occurance of the value is removed if it exists
	//		Returns 1 on success, 0 on failure
	int remove(const int& value);

	// Determine whether or not an item is in the CBag
	// PRE: value is the int to find
	// POST: Returns 1 if the value is in the CBag, 0 if it is not
	int find(const int& value) const;

	// Determine whether or not the CBag is empty
	// PRE: None
	// POST: Returns 1 if the CBag is empty, 0 if it is not
	int isEmpty(void) const;

	// Determine whether or not the CBag is full
	// PRE: None
	// POST: Returns 1 if the CBag is full, 0 if it is not
	int isFull(void) const;

	// Retrieve an element from the CBag
	// PRE: index is the element number to get (first element is index=0)
	//		Note: the element must exist for proper operation
	// POST: Returns the element value (or zero if it does not exist)
	int element(const int& index) const;

	// Get the number of elements in the CBag
	// PRE: None
	// POST: Returns the number of elements in the CBag
	int numberElements(void) const;

private:
	int size;	// The number of elements in the CBag
	int max;	// The max number of elements in the CBag before more memory is needed
	int *elements;		// Pointer to the actual elements for the CBag
};

#endif // !defined(AFX_BAG_H__1EC94D55_85BF_11D4_A46D_006097D2E7B9__INCLUDED_)
