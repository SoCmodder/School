// Hash.h: interface for the CHash class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HASH_H__198676EE_C24D_11D4_AABF_00C0F05923A6__INCLUDED_)
#define AFX_HASH_H__198676EE_C24D_11D4_AABF_00C0F05923A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Hash Class Header
// Ering Pringle and Joe Wingbermuehle

// Name/location of the input file
const char IN_FILE_NAME[]="c:\\shakespear.txt";

// Name/location of the hash file
const char HASH_FILE_NAME[]="c:\\hashfile.153";

const int MAX_LENGTH=30;	// Max length of a word
const int TABLE_SIZE=256;	// Size of the hash table

class CHash {
public:

	// Constructor
	// PRE: none
	// POST: creates an empty CHash
	CHash();

	// Destructor
	// PRE: freeNodes points to the list of empty slots
	// POST: destroys the CHash
	virtual ~CHash();

	// Build a hash table (HASH_FILE_NAME) from IN_FILE_NAME
	// PRE: IN_FILE_NAME contains a list of strings, separated by new lines
	// POST: creates a hash table if possible, returns true on success
	//       or false on failure
	bool Build(void);

	// Initialize the CHash
	// PRE: none
	// POST: the old CHash is deleted and a new one is created
	void Initialize(void);

	// Determine if a string is in the hash table
	// PRE: str points to the string to query
	// POST: returns true if the name is found, otherwise returns
	//       false (returns false also if table does not exist)
	bool Query(const char* str) const;

	// Insert a string to the hash table
	// PRE: str points to the string to insert
	// POST: returns true on success, false on failure
	bool Insert(const char* str);

	// Remove a string from the hash table
	// PRE: str points to the string to remove
	// POST: returns true on success, false on failure
	bool Remove(const char* str);

	// Count the number of empty home positions
	// PRE: none
	// POST: returns the number of empty home positions
	int CountEmpty(void);

	// Count how many items are in the overflow area
	// PRE: none
	// POST: returns the number of items in the overflow area
	int CountOverflow(void);

	// Count the number of words in the hash table
	// PRE: none
	// POST: returns the number of words in the hash table
	long CountWords(void);

	// Find the length of the longest chain
	// PRE: none
	// POST: returns the length of the longest chain
	int CountLongest(void);

	// Get the string that starts the longest chain
	// PRE: none
	// POST: returns the string that starts the longest chain
	CString GetLongest(void);

	// Count the number of holes in the overflow area
	// PRE: none
	// POST: returns the number of holes in the overflow area
	int CountHoles(void);

private:

	// Struct for storing hash nodes
	struct HNode {
		char data[MAX_LENGTH+1];	// The Word
		long next;					// index of the next node
	};

	// Struct for storing free slots in the hash file
	struct FNode {

		// Constructor
		// PRE: in is the next FNode in the list
		// POST: a new FNode is created
		FNode(FNode* in) {next=in;}

		// Default constructor
		// PRE: none
		// POST: a new/empty FNode is created
		FNode() {next=0;}

		// Destructor
		// PRE: none
		// POST: FNode is destroyed
		~FNode() { };

		long value;		// number of the empty slot
		FNode *next;	// pointer to the next node
	};

	FNode *freeNodes;		// Pointer to a list of free slots
	long currentPos;		// Current slot for insert
	bool initialized;		// Hash table initialized? (ie, valid)
	int empty;				// Number of empty home positions
	int overflow;			// Number of overflow slots filled
	long wordCount;			// Number of words in the hash table
	int chainLength[TABLE_SIZE];	// Lengths of the chains

	// Get the hash key for a string
	// PRE: str points to the string for which to obtain the key
	// POST: returns the hash key for the string
	unsigned char GetHash(const char* str) const;

	// Get the position in the file for a given node number
	// PRE: offset is the number of the node
	// POST: returns the file offset for the given node
	long GetPosition(long offset) const;

};

#endif // !defined(AFX_HASH_H__198676EE_C24D_11D4_AABF_00C0F05923A6__INCLUDED_)
