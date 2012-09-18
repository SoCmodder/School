#include <algorithm>
#include <list>
#include <iostream.h>
	
int main()
{
	int ia[]  = { 5, 4, 3, 2, 1, 0 };
	list< int,allocator > ilist( ia, ia+6 );
		
	typedef list< int, allocator >::iterator iterator;
	iterator iter1 = ilist.begin(), 
		 iter2,
	         iter_end = ilist.end();

	// bubble sort the list ...
	for ( ; iter1 != iter_end; ++iter1 )
	      for ( iter2 = iter1; iter2 != iter_end; ++iter2 )
		    if ( *iter2 < *iter1 )
		     	  iter_swap( iter1, iter2 );
		
	// output generated:
	// ilist afer bubble sort using iter_swap(): { 0 1 2 3 4 5 }

	cout << "ilist afer bubble sort using iter_swap(): { ";
	for ( iter1 = ilist.begin(); iter1 != iter_end; ++iter1 )
	      cout << *iter1 << " ";
        cout << "}\n";

	return 0;
}
