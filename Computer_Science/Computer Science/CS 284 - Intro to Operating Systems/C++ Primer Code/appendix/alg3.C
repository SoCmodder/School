#include <algorithm>
#include <vector>
#include <functional>
#include <assert.h>
#include <iostream.h>

int main()
{
	int ia[] = {29,23,20,22,17,15,26,51,19,12,35,40}; 
	vector< int, allocator > vec( ia, ia+12 );

	// ascending order sort using default less-than operator
	sort( &ia[0], &ia[12] );

	// descending order sort using greater-than operator
	sort( vec.begin(), vec.end(), greater<int>() );


	bool found_it = binary_search( &ia[0], &ia[12], 18 );
	assert( found_it == false );
		
	// must let binary_search know relational order ...
	found_it = binary_search( vec.begin(), vec.end(), 26,
		 		  greater<int>() );

	// as an exercise, don't supply greater<int>()
	// element 26 is then not found, and assertion triggered
	assert( found_it == true );

	// still here: assertions evaluated as true
	cout << "binary_search(): success!\n";
		
	return 0;
}
