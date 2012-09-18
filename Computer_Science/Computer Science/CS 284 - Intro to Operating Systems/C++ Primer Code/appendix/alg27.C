#include <algorithm>
#include <vector>
#include <string>
#include <iterator>
#include <assert.h>
	
template <class Type>
void print_elements( Type elem ) { cout << elem << " "; }

void (*pfi)( int ) = print_elements;
void (*pfs)( string ) = print_elements;

int main()
{
	int ia[] = { 0, 1, 0, 2, 0, 3, 0, 4, 0, 5 };

	vector<int,allocator> vec( ia, ia+10 );
	vector<int,allocator>::iterator vec_iter;
		
	// results in unchanged sequence: 0's are not consecutive
// generates: 0 1 0 2 0 3 0 4 0 5
	vec_iter = unique( vec.begin(), vec.end() );
	for_each( vec.begin(), vec.end(), pfi ); cout << "\n\n";
		
	// sort vector, then apply unique: modified
// generates: 0 1 2 3 4 5 2 3 4 5
	sort( vec.begin(), vec.end() );
	vec_iter = unique( vec.begin(), vec.end() );
        for_each( vec.begin(), vec.end(), pfi ); cout << "\n\n";
		
	// erase the invalid elements from container
// generates: 0 1 2 3 4 5 
	vec.erase( vec_iter, vec.end() );
        for_each( vec.begin(), vec.end(), pfi ); cout << "\n\n";

	string sa[] = { "enough", "is", "enough", 
			"enough", "is", "good" };

	vector<string,allocator> svec( sa, sa+6 );
	vector<string,allocator> vec_result( svec.size() );
	vector<string,allocator>::iterator svec_iter;

        sort( svec.begin(), svec.end() );

	svec_iter = unique_copy( svec.begin(), svec.end(), 
				 vec_result.begin() ); 
		
// generates: enough good is
        for_each( vec_result.begin(), svec_iter, pfs ); 
	cout << "\n\n";
		
	return 0;
}
