	#include <algorithm>
	#include <vector>
	#include <utility>
	#include <iostream.h>

/* generates:
array element sequence after sort:
12 15 17 19 20 22 23 26 29 35 40 51 

equal_range result of search for value 23:
        *ia_iter.first: 23      *ia_iter.second: 26

equal_range result of search for absent value 21:
        *ia_iter.first: 22      *ia_iter.second: 22

vector element sequence after sort:
51 40 35 29 26 23 22 20 19 17 15 12 

equal_range result of search for value 26:
        *ivec_iter.first: 26    *ivec_iter.second: 23

equal_range result of search for absent value 21:
        *ivec_iter.first: 20    *ivec_iter.second: 20
*/
	
	int main()
	{
		int ia[] = { 29,23,20,22,17,15,26,51,19,12,35,40 }; 
		vector< int, allocator > ivec( ia, ia+12 );
                ostream_iterator< int >  ofile( cout, " " );

		sort( &ia[0], &ia[12] );

                cout << "array element sequence after sort:\n";
                copy( ia, ia+12, ofile ); cout << "\n\n";

		pair< int*,int* > ia_iter;
		ia_iter = equal_range( &ia[0], &ia[12], 23 );
		
		cout << "equal_range result of search for value 23:\n\t"
		     << "*ia_iter.first: "  << *ia_iter.first << "\t"
		     << "*ia_iter.second: " << *ia_iter.second << "\n\n";
		
		ia_iter = equal_range( &ia[0], &ia[12], 21 );

		cout << "equal_range result of search for absent value 21:\n\t"
		     << "*ia_iter.first: "  << *ia_iter.first << "\t"
		     << "*ia_iter.second: " << *ia_iter.second << "\n\n";
		
		sort( ivec.begin(), ivec.end(), greater<int>() );

                cout << "vector element sequence after sort:\n";
                copy( ivec.begin(), ivec.end(), ofile ); cout << "\n\n";
		
		typedef vector< int, allocator >::iterator iter_ivec;
		pair< iter_ivec, iter_ivec > ivec_iter;

		ivec_iter = equal_range( ivec.begin(), ivec.end(), 26, 
					 greater<int>() );
		
		cout << "equal_range result of search for value 26:\n\t"
		     << "*ivec_iter.first: "  << *ivec_iter.first << "\t"
		     << "*ivec_iter.second: " << *ivec_iter.second << "\n\n";

		ivec_iter = equal_range( ivec.begin(), ivec.end(), 21, 
                                         greater<int>() );

		cout << "equal_range result of search for absent value 21:\n\t"
		     << "*ivec_iter.first: "  << *ivec_iter.first << "\t"
		     << "*ivec_iter.second: " << *ivec_iter.second << "\n\n";
	}
