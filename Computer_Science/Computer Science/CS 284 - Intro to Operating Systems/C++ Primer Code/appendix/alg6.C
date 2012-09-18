#include <algorithm>
#include <list>
#include <iostream.h>
#include <assert.h>
	
class Even {
public:
	bool operator()( int val ) 
		{ return val%2 ? false : true; }
};
	
int main() 
{
	int ia[] = {0,1,1,2,3,5,8,13,21,34};
	list< int,allocator > ilist( ia, ia+10 );
		
        /*
         * unsupported in current implementation
         *****************************************************
	 typedef 
	    iterator_traits<InputIterator>::distance_type
	    distance_type;
	
	    distance_type ia_count, list_count;
		
	    // count even elements: 4 
	    ia_count = count_if( &ia[0], &ia[10], Even() );
	    list_count = count_if( ilist.begin(), ilist_end(),
			           bind2nd(less<int>(),10) );
	  ******************************************************
	  */

	int ia_count = 0;
        count_if( &ia[0], &ia[10], Even(), ia_count );

	// generates: 
	//   count_if(): there are 4 elements that are even.

	cout << "count_if(): there are "
	     << ia_count << " elements that are even.\n";

	int list_count = 0;
        count_if( ilist.begin(), ilist.end(),
	          bind2nd(less<int>(),10), list_count );


	// generates: 
	//   count_if(): there are 7 elements that are less than 10.

	cout << "count_if(): there are "
	     << list_count 
	     << " elements that are less than 10.\n";
		
	return 0;
}
