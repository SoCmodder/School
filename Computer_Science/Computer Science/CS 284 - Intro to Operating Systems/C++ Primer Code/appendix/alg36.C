#include <algorithm>
#include <vector>
#include <iostream.h>
	
int main()
{
	vector< int, allocator > vec;
	for ( int ix = 0; ix < 20; ix++ )
	      vec.push_back( ix );
		
	random_shuffle( vec.begin(), vec.end() );
		
	// generates:
	// random_shuffle of sequence of values 1 .. 20:
	// 6 11 9 2 18 12 17 7 0 15 4 8 10 5 1 19 13 3 14 16
	cout << "random_shuffle of sequence of values 1 .. 20:\n";
	copy( vec.begin(), vec.end(), ostream_iterator< int >( cout," " ));
		
	return 0;
}
