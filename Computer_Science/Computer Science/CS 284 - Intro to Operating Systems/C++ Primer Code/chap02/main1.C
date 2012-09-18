// #include <iostream>
#include <iostream.h>
#include "IntArray.h"
#include "IntArrayRC.h"

/**
 **
 swap() with IntArray ia1
 swap() with IntArrayRC ia2
 Assertion failed: ix >= 0 && ix < _size, file IntArrayRC.h, line 19
 **
 **/

void swap( IntArray &ia, int ix, int jx )
{
	// subscript operator is virtual invocation

	int tmp  = ia[ ix ];
	ia[ ix ] = ia[ jx ];
	ia[ jx ] = tmp;
}

int main()
{
 	int array[ 4 ] = { 0, 1, 2, 3 };
 	IntArray ia1( array, 4 );
 	IntArrayRC ia2( array, 4 );

 	// error: off-by-one: should be size-1
 	// not caught by IntArray object

 	cout << "swap() with IntArray ia1" << endl;
 	swap( ia1, 1, ia1.size() );

 	// ok: caught by IntArrayRC object
 	cout << "swap() with IntArrayRC ia2" << endl;
 	swap( ia2, 1, ia2.size() );

 	return 0;
}
