#include <algorithm>
#include <vector>
#include <iostream.h>
	
int main()
{
	int ia[] = {29,23,20,22,17,15,26,51,19,12,35,40}; 
	sort( &ia[0], &ia[12] );

	int search_value = 18;
	int *ptr = lower_bound( ia, ia+12, search_value );

	// generates:
	// The first element 18 can be inserted in front of is 19
	// The previous value is 17

	cout << "The first element " 
	     << search_value 
	     << " can be inserted in front of is "
	     << *ptr << endl
	     << "The previous value is "
	     << *(ptr-1) << endl;
		
	vector< int, allocator > ivec( ia, ia+12 );

	// sort in descending order ...
	sort( ivec.begin(), ivec.end(), greater<int>() );
		
	search_value = 26;
	vector< int, allocator >::iterator iter;

	// have to tell it appropriate ordering 
        // relationship to use in this case ...

	iter = lower_bound( ivec.begin(), ivec.end(), 
	  		    search_value, greater<int>() );

	// generates:
	// The first element 26 can be inserted in front of is 26
	// The previous value is 29

	cout << "The first element " 
	     << search_value 
	     << " can be inserted in front of is "
	     << *iter << endl
	     << "The previous value is "
	     << *(iter-1) << endl;
	
	return 0;
}
