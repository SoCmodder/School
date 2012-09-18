#include <algorithm>
#include <list>
#include <string>
#include <assert.h>
#include <iostream.h>
	
class size_compare {
public:
	bool operator()( const string &a, const string &b ) {
	     return a.length() <= b.length();
	}
};
	
int main()
{
	string arr1[] = { "Piglet", "Pooh", "Tigger" };
	string arr2[] = { "Piglet", "Pooch", "Eeyore" };
		
	bool res;
		
	// evaluates to false at second element
	// Pooch is less than Pooh
	// would also evaluate false at 3rd element

	res = lexicographical_compare( arr1, arr1+3,
				       arr2, arr2+3 );

	assert( res == false );
		
	// evaluates to true: each element of ilist2
	// has a length less-than or equal to the
	// associated ilist1 element

	list< string, allocator > ilist1( arr1, arr1+3 );
	list< string, allocator > ilist2( arr2, arr2+3 );
		
	res = lexicographical_compare( 
	         ilist1.begin(), ilist1.end(), 
	         ilist2.begin(), ilist2.end(), size_compare() );
		
	assert( res == true );
	
	cout << "ok: lexicographical_compare succeeded!\n";
}
