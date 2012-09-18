#include <algorithm>
#include <vector>
#include <iostream.h>
#include <assert.h>
	
class TwiceOver {
public:
	bool operator() ( int val1, int val2 ) 
	{
	     return val1 == val2/2 ? true : false;
	}
};
	
int main() 
{
	int ia[] = { 1, 4, 4, 8 };
	vector< int, allocator > vec( ia, ia+4 );

        int *piter;
	vector< int, allocator >::iterator iter;
		
	// piter points to ia[1] 
	piter = adjacent_find( ia, ia+4 );
	assert( *piter = ia[ 1 ] );
		
	// iter points to vec[2] 
	iter = adjacent_find( vec.begin(), vec.end(), TwiceOver() );
	assert( *iter = vec[ 2 ] );

	// reach here: everything ok
	cout << "ok: adjacent-find() succeeded!\n";
		
	return 0;
}
