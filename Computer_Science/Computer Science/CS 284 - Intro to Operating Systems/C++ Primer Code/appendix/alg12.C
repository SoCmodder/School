#include <algorithm>
#include <vector>
#include <iostream.h>
#include <assert.h>
	
int main() 
{
	int array[ 17 ]   = { 7,3,3,7,6,5,8,7,2,1,3,7,6,3,8,4,3 };
	int subarray[ 3 ] = { 3, 7, 6 };
		
	int *found_it; 

	// find the last occurrence of the sequence 3,7,6
	// in array, and return address of first element ...

        found_it = find_end( &array[0],    &array[17], 
		   	     &subarray[0], &subarray[3] );
		
	assert( found_it == &array[10] );
		
	vector< int, allocator > ivec( array, array+17 );
	vector< int, allocator > subvec( subarray, subarray+3 );
		
	vector< int, allocator >::iterator found_it2; 

	found_it2 = find_end( ivec.begin(),   ivec.end(), 
		 	      subvec.begin(), subvec.end(),
			      equal_to<int>() );
		
	assert( found_it2 == ivec.begin()+10 );

	cout << "ok: find_end correctly returned beginning of "
	     << "last matching sequence: 3,7,6!\n";
		
	return 0;
}
