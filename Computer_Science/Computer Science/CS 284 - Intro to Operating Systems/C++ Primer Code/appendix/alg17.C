#include <algorithm>
#include <vector>
#include <iostream.h>
	
int main()
{
	int ia1[] = { 13, 1, 21, 2, 0, 34, 5, 1, 8, 3, 21, 34 }; 
	int ia2[] = { 21, 2, 8, 3, 5, 1 };
		
	// includes must be passed sorted containers
	sort( ia1, ia1+12 ); sort( ia2, ia2+6 );

	// generates: every element of ia2 contained in ia1? true

	bool res = includes( ia1, ia1+12, ia2, ia2+6 );
	cout << "every element of ia2 contained in ia1? "
	     << (res ? "true" : "false") << endl;

	vector< int, allocator > ivect1( ia1, ia1+12 );
	vector< int, allocator > ivect2( ia2, ia2+6 );

	// sort in descending order
	sort( ivect1.begin(), ivect1.end(), greater<int>() ); 
	sort( ivect2.begin(), ivect2.end(), greater<int>() );
		
	res = includes( ivect1.begin(), ivect1.end(),
			ivect2.begin(), ivect2.end(), greater<int>() );

	// generates: every element of ivect2 contained in ivect1? true

	cout << "every element of ivect2 contained in ivect1? "
	     << (res ? "true" : "false") << endl;

}

