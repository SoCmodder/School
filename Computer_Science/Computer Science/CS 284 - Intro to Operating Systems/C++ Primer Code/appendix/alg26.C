#include <algorithm>
#include <vector>
#include <assert.h>
#include <iostream.h>
	
template <class Type>
void print_elements( Type elem ) { cout << elem << " "; }

void (*pfi)( int ) = print_elements;

int main()
{
	int ia[] = {29,23,20,22,17,15,26,51,19,12,35,40}; 
	vector<int,allocator> vec(ia,ia+12);
		
	sort(ia,ia+12);
	int *iter = upper_bound(ia,ia+12,19);
	assert( *iter == 20 );
		
	sort( vec.begin(), vec.end(), greater<int>() );
	vector<int,allocator>::iterator iter_vec;

	iter_vec = upper_bound( vec.begin(), vec.end(), 
				27, greater<int>() );

	assert( *iter_vec == 26 );
		
	// generates: 51 40 35 29 27 26 23 22 20 19 17 15 12 
	vec.insert( iter_vec, 27 );
	for_each( vec.begin(), vec.end(), pfi ); cout << "\n\n";
		
	return 0;
}
