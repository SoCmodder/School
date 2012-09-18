// Vect.cpp: implementation of the CVect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "prog3.h"
#include "Vect.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Create a CVect from a CString
CVect::CVect(const CString& input) {
	char str[MAX_LENGTH+1];		// string to hold the input
	char seps[]=" ,";			// separators for the vector elements
	char *temp;					// pointer to current location in the string

	// Initialize
	strcpy(str,input);
	valueCount=0;
	temp=strtok(str,seps);

	// Loop through, extracting the signed ints and adding them to the CVect
	while(valueCount<=MAX_NUMBER && temp) {
		// Convert temp to a value and add it to our CVect
		values[valueCount++]=atoi(temp);
		temp=strtok(NULL,seps);
	}
}

// Create an empty CVect
CVect::CVect()
{
	valueCount=0;		// Create an empty CVect (number of elements=0)
}

// Destroy the CVect
CVect::~CVect()
{
	// Nothing needed
}

// Add two CVects and return the sum
CVect CVect::operator +(const CVect& input) const {
	CVect ans;			// The CVect we will return

	// If the inputs differ in the number of elements return an empty CVect
	ans.valueCount=0;
	if(valueCount==input.valueCount) {

		// Loop through and add each element and save to ans
		for(int x=0;x<valueCount;x++) {
			ans.values[x]=values[x]+input.values[x];
		}
		ans.valueCount=valueCount;
	}
	return ans;
}

// Subtract the input CVect from the calling CVect and return the difference
CVect CVect::operator -(const CVect& input) const {
	CVect ans;		// The CVect we will return

	// Return an empty CVect if the inputs differ in the number of elements
	ans.valueCount=0;
	if(valueCount==input.valueCount) {

		// Loop through subtracting each element and save the result to ans
		for(int x=0;x<valueCount;x++) {
			ans.values[x]=values[x]-input.values[x];
		}
		ans.valueCount=valueCount;
	}
	return ans;
}

// Find the dot product of two CVects
CVect CVect::operator *(const CVect& input) const {
	CVect ans;			// The CVect we will return

	// If the inputs differ in the number of elements return an empty CVect
	ans.valueCount=0;
	if(valueCount==input.valueCount && valueCount) {
		CVect temp;		// CVect to hold the products
		int x;			// Index variable

		// Assign the product of both inputs to temp
		temp.valueCount=valueCount;
		for(x=0;x<valueCount;x++) {
			temp.values[x]=values[x]*input.values[x];
		}

		// Add up all the elements of temp and put the result in the
		// first element of ans
		ans.values[0]=0;
		for(x=0;x<temp.valueCount;x++) {
			ans.values[0]+=temp.values[x];
		}
		ans.valueCount=1;
	}
	return ans;
}

// Assign a CString list to a CVect
CVect CVect::operator =(const CString& input) {
	CVect ans(input);		// Create a new object with the input
	return ans;
}

// Create a char* for the vector
char *CVect::toString(void) const {
	static char srep[MAX_LENGTH+1];	// String representation of the CVect
	char temp[MAX_LENGTH+1];		// Temporary string for conversion of int to char*

	// Loop through each element and append a char* verion to srep
	srep[0]=0;
	for(int x=0;x<valueCount;x++) {
		itoa(values[x],temp,10);
		if(srep[0]) strcat(srep,", ");
		strcat(srep,temp);
	}
	return srep;
}

// Return the number of values in the vector
int CVect::length(void) const {
	return valueCount;
}