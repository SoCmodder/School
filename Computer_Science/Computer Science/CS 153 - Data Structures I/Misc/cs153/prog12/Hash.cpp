// Hash.cpp: implementation of the CHash class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "prog12.h"
#include "Hash.h"
#include <iostream.h>
#include <istream.h>
#include <ostream.h>
#include <fstream.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// Hash Class Implementation
// Erin Pringle and Joe Wingbermuehle

// Constructor
// PRE: none
// POST: creates an empty CHash
CHash::CHash() {

	// Initialize some variables
	freeNodes=0;
	initialized=false;
	empty=TABLE_SIZE;
	overflow=0;
	wordCount=0;

	// Initialize the chainLength array
	for(int x=0;x<TABLE_SIZE;x++) {
		chainLength[x]=0;
	}
}

// Destructor
// PRE: freeNodes points to the list of empty slots
// POST: destroys the CHash
CHash::~CHash() {
	FNode *temp;	// Temporary pointer

	while(freeNodes) {
		temp=freeNodes->next;
		delete freeNodes;
		freeNodes=temp;
	}
}


// Build a hash table (HASH_FILE_NAME) from IN_FILE_NAME
// PRE: IN_FILE_NAME contains a list of strings, separated by new lines
// POST: creates a hash table if possible, returns true on success
//       or false on failure
bool CHash::Build(void) {
	ifstream inFile(IN_FILE_NAME,ios::in);
	fstream outFile(HASH_FILE_NAME,ios::in|ios::out|ios::binary);

	char str[MAX_LENGTH+1];	// String as read from input file
	HNode temp;				// Temporary storage for a node
	unsigned char hash;		// Hash key of the current string
	long oldPos;			// Position of the last record inserted

	// Return false if files could not be opened
	if(!inFile || !outFile) {
		inFile.close();
		outFile.close();
		return false;
	}

	Initialize();

	// Create the hash table
	for(;;) {
		outFile.clear();
		inFile >> str;
		if(inFile.eof()) {
			break;
		}

		hash=GetHash(str);
		outFile.seekg(GetPosition(hash));
		outFile.read((char*)(&temp),sizeof(temp));
		++wordCount;

		if(temp.next==-2) {		// Home position empty
			temp.next=-1;
			outFile.seekp(GetPosition(hash));
			--empty;
		} else {				// Home position occupied
			++overflow;
			++chainLength[hash];

			oldPos=temp.next;
			temp.next=currentPos;
			outFile.seekp(GetPosition(hash));
			outFile.write((char*)(&temp),sizeof(temp));
			outFile.seekp(GetPosition(currentPos));
			++currentPos;
			temp.next=oldPos;
		}
		strcpy(temp.data,str);
		outFile.write((char*)(&temp),sizeof(temp));
	}

	// Write the current position to the beginning of the file
	outFile.seekp(0);
	outFile.write((char*)(&currentPos),sizeof(currentPos));

	inFile.close();
	outFile.close();
	initialized=true;
	return true;
}

// Initialize the CHash
// PRE: none
// POST: the old CHash is deleted and a new one is created
void CHash::Initialize(void) {
	ofstream outFile(HASH_FILE_NAME,ios::out);
	HNode temp;		// Temporary HNode
	FNode *fn;		// Temporary pointer
	int x;			// Index variable

	if(!outFile) return;

	// Delete old free node list
	while(freeNodes) {
		fn=freeNodes->next;
		delete freeNodes;
		freeNodes=fn;
	}

	// Set default home position node
	temp.next=-2;
	temp.data[0]=0;

	// Initialize status variables
	wordCount=0;
	empty=TABLE_SIZE;
	overflow=0;

	// Create an empty table
	currentPos=TABLE_SIZE;
	outFile.write((char*)(&currentPos),sizeof(currentPos));
	for(x=0;x<TABLE_SIZE;x++) {
		outFile.write((char*)(&temp),sizeof(temp));
		chainLength[x]=0;
	}

	outFile.close();
	initialized=true;
}

// Determine if a string is in the hash table
// PRE: str points to the string to query
// POST: returns true if the name is found, otherwise returns
//       false (returns false also if table does not exist)
bool CHash::Query(const char* str) const {
	ifstream inFile(HASH_FILE_NAME,ios::in|ios::binary);
	HNode temp;			// Temporary HNode

	if(!inFile || !initialized) {
		inFile.close();
		return false;
	}

	// See if the string is in the hash table
	temp.next=GetHash(str);
	while(temp.next>=0) {
		inFile.seekg(GetPosition(temp.next));
		inFile.read((char*)(&temp),sizeof(temp));
		if(temp.next!=-2 && !strcmp(temp.data,str)) {
			inFile.close();
			return true;
		}
	}

	inFile.close();
	return false;
}

// Insert a string to the hash table
// PRE: str points to the string to insert
// POST: returns true on success, false on failure
bool CHash::Insert(const char* str) {
	fstream outFile;					// Hash file stream
	HNode temp;							// Temporary HNode
	unsigned char hash=GetHash(str);	// Hash key of the string
	long oldNext;						// Previous "next" index

	if(!initialized) {
		Initialize();
	}

	outFile.open(HASH_FILE_NAME,ios::in|ios::out|ios::binary);

	if(!outFile) {
		return false;
	}

	outFile.read((char*)(&currentPos),sizeof(currentPos));

	outFile.seekg(GetPosition(hash));
	outFile.read((char*)(&temp),sizeof(temp));
	++wordCount;
	if(temp.next==-2) {			// Home position is empty
		--empty;
		temp.next=-1;
		outFile.seekp(GetPosition(hash));
	} else if(freeNodes) {		// Home position full, but empty slots exist
		FNode *fn;
		++overflow;
		++chainLength[hash];

		oldNext=temp.next;
		temp.next=freeNodes->value;
		fn=freeNodes->next;
		delete freeNodes;
		freeNodes=fn;

		outFile.seekp(GetPosition(hash));
		outFile.write((char*)(&temp),sizeof(temp));
		outFile.seekp(GetPosition(temp.next));
		temp.next=oldNext;
	} else {			// Need to create a new slot
		++overflow;
		++chainLength[hash];

		oldNext=temp.next;
		temp.next=currentPos;
		outFile.seekp(GetPosition(hash));
		outFile.write((char*)(&temp),sizeof(temp));
		temp.next=oldNext;
		outFile.seekp(GetPosition(currentPos));

		++currentPos;
	}

	// Write the string to the hash
	strcpy(temp.data,str);
	outFile.write((char*)(&temp),sizeof(temp));

	// Write the current position
	outFile.seekp(0);
	outFile.write((char*)(&currentPos),sizeof(currentPos));

	outFile.close();

	return true;
}

// Remove a string from the hash table
// PRE: str points to the string to remove
// POST: returns true on success, false on failure
bool CHash::Remove(const char* str) {
	fstream outFile(HASH_FILE_NAME,ios::in|ios::out|ios::binary);
	HNode temp;			// Temporary (current) HNode
	HNode prev;			// Previously visited HNode
	long removePos;		// Position to remove
	long prevPos;		// Previous position
	unsigned char hash=GetHash(str);	// Hash key of the string

	if(!outFile) {
		return false;
	}

	outFile.read((char*)(&currentPos),sizeof(currentPos));

	// Find record to remove
	temp.next=hash;
	removePos=0;
	while(temp.next>=0) {

		prev=temp;
		prevPos=removePos;
		removePos=temp.next;
		outFile.seekg(GetPosition(temp.next));
		outFile.read((char*)(&temp),sizeof(temp));

		// Remove the string if it matches
		if(temp.next!=-2 && !strcmp(temp.data,str)) {

			// Remove the record
			if(removePos<TABLE_SIZE) {	// In home position
				if(temp.next==-1) {	// Last entry
					++empty;
					temp.next=-2;
					outFile.seekp(GetPosition(removePos));
					outFile.write((char*)(&temp),sizeof(temp));
				} else {	// More entries follow
					--overflow;
					--chainLength[hash];

					outFile.seekg(GetPosition(temp.next));
					outFile.read((char*)(&prev),sizeof(HNode));
					freeNodes=new FNode(freeNodes);
					freeNodes->value=temp.next;
					outFile.seekp(GetPosition(removePos));
					outFile.write((char*)(&prev),sizeof(HNode));
				}	
			} else {	// Not in home position
				--overflow;
				--chainLength[hash];

				freeNodes=new FNode(freeNodes);
				freeNodes->value=removePos;
				prev.next=temp.next;
				outFile.seekp(GetPosition(prevPos));
				outFile.write((char*)(&prev),sizeof(HNode));
			}

			--wordCount;
			return true;

		}
	}

	outFile.close();

	return false;
}

// Get the hash key for a string
// PRE: str points to the string for which to obtain the key
// POST: returns the hash key for the string
inline unsigned char CHash::GetHash(const char* str) const {
	unsigned char hash=0;

	for(int x=0;str[x];hash+=str[x++]);

	return hash;
}

// Get the position in the file for a given node number
// PRE: offset is the number of the node
// POST: returns the file offset for the given node
long CHash::GetPosition(long offset) const {
	return offset*sizeof(HNode)+sizeof(currentPos);
}

// Count the number of empty home positions
// PRE: none
// POST: returns the number of empty home positions
int CHash::CountEmpty(void) {
	return empty;
}

// Count how many items are in the overflow area
// PRE: none
// POST: returns the number of items in the overflow area
int CHash::CountOverflow(void) {
	return overflow;
}

// Count the number of words in the hash table
// PRE: none
// POST: returns the number of words in the hash table
long CHash::CountWords(void) {
	return wordCount;
}

// Find the length of the longest chain
// PRE: none
// POST: returns the length of the longest chain
int CHash::CountLongest(void) {
	int longest=0;		// Length of the longest chain

	// Determine which chain is longest
	for(int x=0;x<TABLE_SIZE;x++) {
		if(chainLength[x]>longest) {
			longest=chainLength[x];
		}
	}

	return longest;
}

// Get the string that starts the longest chain
// PRE: none
// POST: returns the string that starts the longest chain
CString CHash::GetLongest(void) {
	ifstream inFile(HASH_FILE_NAME,ios::in|ios::binary);
	int longest=CountLongest();		// Length of the longest chain
	int index;						// To become the index of the longest chain
	HNode temp;						// Temporary HNode

	if(!inFile || !initialized) {
		inFile.close();
		return "";
	}

	// Get the index for the longest chain
	for(index=0;chainLength[index]!=longest;index++);

	inFile.seekg(GetPosition(index));
	inFile.read((char*)(&temp),sizeof(HNode));

	inFile.close();

	return temp.data;
}

// Count the number of holes in the overflow area
// PRE: none
// POST: returns the number of holes in the overflow area
int CHash::CountHoles(void) {
	FNode *fn=freeNodes;		// Pointer to the current node
	int count=0;				// Number of nodes visited so far

	while(fn) {
		++count;
		fn=fn->next;
	}

	return count;
}
