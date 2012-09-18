#include <algorithm>
#include <vector>
#include <list>
#include <deque>

template <class Type>
void print_elements( Type elem ) { cout << elem << " "; }

void (*pfi)( int ) = print_elements;

int main()
{
	int ia[] =  {29,23,20,22,17,15,26,51,19,12,35,40}; 
	int ia2[] = {74,16,39,54,21,44,62,10,27,41,65,71};

	vector< int, allocator > vec1( ia,  ia +12 ), 
                                         vec2( ia2, ia2+12 );
	int ia_result[24];
	vector< int, allocator > vec_result( vec1.size()+vec2.size() );
		
	sort( ia,  ia +12 );   
        sort( ia2, ia2+12 );

// generates: 10 12 15 16 17 19 20 21 22 23 26 27 29 35 39 40 41 44 51 54 62 65 71 74 
	merge( ia, ia+12, ia2, ia2+12, ia_result );
	for_each( ia_result, ia_result+24, pfi ); cout << "\n\n";

	sort( vec1.begin(), vec1.end(), greater<int>() );
	sort( vec2.begin(), vec2.end(), greater<int>() );

	merge( vec1.begin(), vec1.end(),
               vec2.begin(), vec2.end(),
	vec_result.begin(), greater<int>() );

// generates: 74 71 65 62 54 51 44 41 40 39 35 29 27 26 23 22 21 20 19 17 16 15 12 10 
        for_each( vec_result.begin(), vec_result.end(), pfi ); cout << "\n\n";

	return 0;
}
