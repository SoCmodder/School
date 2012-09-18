#include <algorithm>
#include <list>
#include <iostream.h>
	
class equal_and_odd{
public:
	bool 
	operator()( int val1, int val2 )
        {
		return ( val1 == val2 && 
		       ( val1 == 0 || val1 % 2 )) 
				? true : false;
	}
};
	
int main() 
{
	int ia[] =  { 0,1,1,2,3,5,8,13 };
	int ia2[] = { 0,1,1,2,3,5,8,13,21,34 };

	bool res;
		
        // true: both are equal to the length of ia. 
	// generates: int ia[7] equal to int ia2[9]? true.

	res = equal( &ia[0], &ia[7], &ia2[0] );
	cout << "int ia[7] equal to int ia2[9]? "
	     << ( res ? "true" : "false" ) << ".\n";
		
        // false: not equal to the length of ia2. 
	// note: dangerous since ia[8] and ia[9] do not exist!
	// generates: int ia2[9] equal to int ia[7]? false.

	res = equal( &ia2[0], &ia2[9], &ia[0] );
	cout << "int ia2[9] equal to int ia[7]? "
	     << ( res ? "true" : "false" ) << ".\n";

	list< int, allocator > ilist(  ia,  ia+7  );
	list< int, allocator > ilist2( ia2, ia2+9 );
		
	// generates: list ilist equal to ilist2? true.

	res = equal( ilist.begin(), ilist.end(), ilist2.begin() );
	cout << "list ilist equal to ilist2? "
	     << ( res ? "true" : "false" ) << ".\n";

  	// false: 0, 2, 8 are not equal and odd
	// generates: list ilist equal_and_odd() to ilist2? false.

	res = equal( ilist.begin(), ilist.end(),
		     ilist2.begin(), equal_and_odd() );

	cout << "list ilist equal_and_odd() to ilist2? "
	     << ( res ? "true" : "false" ) << ".\n";
		
	return 0;
}
