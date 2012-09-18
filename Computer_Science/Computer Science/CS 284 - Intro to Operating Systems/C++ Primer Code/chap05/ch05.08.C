// #include <iostream>
#include <iostream.h>

/**
 ** The sum of the first eight elements of the Fibonacci series is 33
 **/

int sumit( int *parray_begin, int *parray_end )
{
	int sum = 0;
	if ( ! parray_begin || ! parray_end )
	     return sum;

	while ( parray_begin != parray_end )
 		sum += *parray_begin++;

	return sum;
}

int ia[8] = { 0, 1, 1, 2, 3, 5, 8, 13 };
int main()
{
    cout << "The sum of the first eight elements of "
	 << "the Fibonacci series is "
	 << sumit( ia, ia+8 ) 
	 << endl;
}
