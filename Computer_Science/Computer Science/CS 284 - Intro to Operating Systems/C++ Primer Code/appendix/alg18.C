#include <numeric>
#include <vector>
#include <iostream.h>
	
int main()
{
	int ia[] =  { 2, 3, 5, 8 };
	int ia2[] = { 1, 2, 3, 4 };

	// multiply the element pair from the two arrays
	// then add to the initial value: 0

	int res = inner_product( &ia[0], &ia[4], &ia2[0], 0); 

	// generates: inner product of arrays: 55
	cout << "inner product of arrays: "
	     << res << endl;
		
	vector<int, allocator> vec(  ia,  ia+4 );
	vector<int, allocator> vec2( ia2, ia2+4 );

	// add the element pair from the two vectors
	// then subtract from the initial value: 0

	res = inner_product( vec.begin(), vec.end(), 
			     vec2.begin(), 0, 
			     minus<int>(), plus<int>() );

	// generates: inner product of vectors: -28
	cout << "inner product of vectors: "
	     << res << endl;
		
	return 0;
}
