#include <numeric>
#include <list>
#include <functional>
#include <iostream.h>

/*
 * output:
 * accumulate()
 * 	operating on values {1,2,3,4}
 *	result with default addition: 10
 *	result with plus<int> function object: 10
 */

int main()
{
	int ia[] = { 1, 2, 3, 4 };
	list<int,allocator> ilist( ia, ia+4 );
		
	int ia_result = accumulate(&ia[0], &ia[4], 0); 
	int ilist_res = accumulate(
		ilist.begin(), ilist.end(), 0, plus<int>() );

	cout << "accumulate()\n\t"
	     << "operating on values {1,2,3,4}\n\t"
	     << "result with default addition: " 
	     << ia_result << "\n\t"
	     << "result with plus<int> function object: " 
	     << ilist_res 
	     << endl;
		
	return 0;
}
