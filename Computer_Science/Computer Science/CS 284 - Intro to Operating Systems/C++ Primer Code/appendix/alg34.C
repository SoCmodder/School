#include <algorithm>
#include <vector>
#include <iostream.h>
	
class even_elem {
public:
	bool operator()( int elem ) { return elem%2 ? false : true; }
};
	
/*
 * generates:
   original order of elements: 
   29 23 20 22 17 15 26 51 19 12 35 40 
   partition based on whether element is even:
   40 12 20 22 26 15 17 51 19 23 35 29 
   partition based on whether element is less than 25:
   12 23 20 22 17 15 19 51 26 29 35 40 
*/

int main()
{
	const int ia_size = 12;
	int ia[ia_size]   = { 29,23,20,22,17,15,26,51,19,12,35,40 }; 

	vector< int, allocator > vec( ia, ia+ia_size );
	ostream_iterator< int >  outfile( cout, " "  );

	cout << "original order of elements: \n";
	copy( vec.begin(), vec.end(), outfile ); cout << endl;
		
	cout << "partition based on whether element is even:\n";
	partition( &ia[0], &ia[ia_size], even_elem() );
	copy( ia, ia+ia_size, outfile ); cout << endl;	

	cout << "partition based on whether element is less than 25:\n";
	partition( vec.begin(), vec.end(), bind2nd(less<int>(),25)  );
	copy( vec.begin(), vec.end(), outfile ); cout << endl;	

	return 0;
}
