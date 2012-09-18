#include <algorithm>
#include <vector>
#include <iostream.h>

/* 
* generates:
  original order of the vector: 69 23 80 42 17 15 26 51 19 12 35 8 
  partial sort of vector: seven elements
  8 12 15 17 19 23 26 80 69 51 42 35 
  partial_sort_copy() of first seven elements
         of vector in descending order
  26 23 19 17 15 12 8 


*/
	
int main()
{
	int ia[] = {69,23,80,42,17,15,26,51,19,12,35,8 }; 
	vector< int,allocator > vec( ia, ia+12 );
	ostream_iterator<int> out( cout," " ); 
		
	cout << "original order of the vector: ";
	copy( vec.begin(), vec.end(), out ); cout << endl;

        cout << "partial sort of vector: seven elements\n";
        partial_sort( vec.begin(), vec.begin()+7, vec.end() );
        copy( vec.begin(), vec.end(), out ); cout << endl;

	vector< int, allocator > res(7);
        cout << "partial_sort_copy() of first seven elements\n\t"
	     << "of vector in descending order\n";

        partial_sort_copy( vec.begin(), vec.begin()+7, res.begin(), 
			   res.end(), greater<int>() );
        copy( res.begin(), res.end(), out ); cout << endl;

	return 0;
}
