#include <numeric>
#include <list>
#include <functional>
#include <iterator>
#include <iostream.h>

int main()
{
	int ia[] = { 1, 1, 2, 3, 5, 8 };

	list<int,allocator> ilist(ia, ia+6);
	list<int,allocator> ilist_result(ilist.size());


	adjacent_difference(ilist.begin(), ilist.end(), 
			    ilist_result.begin() );
		
	// generates output: 1 0 1 1 2 3 
	copy( ilist_result.begin(), ilist_result.end(),
	      ostream_iterator<int>(cout," "));
		
	cout << endl;

	adjacent_difference(ilist.begin(), ilist.end(), 
			    ilist_result.begin(), times<int>() );

	// generates output: 1 1 2 6 15 40
	copy( ilist_result.begin(), ilist_result.end(),
	      ostream_iterator<int>(cout," "));

	return 0;
}

// *** note: first element is itself. see rogue wave discussion.

