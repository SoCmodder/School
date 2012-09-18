// #include <iostream>
#include <iostream.h>
#include "Array.C"
#include "ArrayRC.C"

/**
 **
 swap() with Array<int> ia1
 swap() with ArrayRC<int> ia2
 Assertion failed: ix >= 0 && ix < Array<elemType>::_size, file ArrayRC.C, line 21
 **
 **/

template <class elemType>
inline void 
swap( Array<elemType> &array, int i, int j ) 
{ 
 	elemType tmp = array[ i ];
 	array[ i ] = array[ j ];
 	array[ j ] = tmp;
}

int main() 
{
 	Array<int>   ia1;
 	ArrayRC<int> ia2;

 	cout << "swap() with Array<int> ia1" << endl;
 	int size = ia1.size();
 	swap( ia1, 1, size );

 	cout << "swap() with ArrayRC<int> ia2" << endl;
 	size = ia2.size();
 	swap( ia2, 1, size );

 	return 0;
}

