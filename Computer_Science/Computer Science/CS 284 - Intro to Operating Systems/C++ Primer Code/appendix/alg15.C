#include <algorithm>
#include <list>
#include <iostream.h>
	
int odd_by_twos() { 
	static int seed = -1; 
	return seed += 2;
}

template <class Type>
void print_elements( Type elem ) { cout << elem << " "; }
	
int main()
{
	list< int, allocator > ilist( 10 );
	void (*pfi)( int ) = print_elements;
		
	generate( ilist.begin(), ilist.end(), odd_by_twos );

	// generates:
	// elements within list the first invocation:
	// 1 3 5 7 9 11 13 15 17 19 

	cout << "elements within list the first invocation:\n";
	for_each( ilist.begin(), ilist.end(), pfi );
		
	generate( ilist.begin(), ilist.end(), odd_by_twos );

	// generates: 
	// elements within list the second iteration:
	// 21 23 25 27 29 31 33 35 37 39 
	cout << "\n\nelements within list the second iteration:\n";
	for_each( ilist.begin(), ilist.end(), pfi );
		
	return 0;
}
