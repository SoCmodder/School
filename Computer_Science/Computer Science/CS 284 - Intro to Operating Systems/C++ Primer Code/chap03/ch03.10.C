// #include <iostream>
#include <iostream.h>
#include <string>

template <class elemType>
void print( elemType *pbegin, elemType *pend )
{
	while ( pbegin != pend ) 
        	cout << *pbegin++ << ' ';
	cout << endl;
}

/**
 **
0 1 1 2 3 5 8 13 21 
3.14 6.28 12.56 25.12 
Piglet Eeyore Pooh 
 **
 **/

int main()
{
    int ia[ 9 ]    = { 0, 1, 1, 2, 3, 5, 8, 13, 21 };
    double da[ 4 ] = { 3.14, 6.28, 12.56, 25.12    };
    string sa[ 3 ] = { "Piglet", "Eeyore", "Pooh"  };

    print( ia, ia+9 );
    print( da, da+4 );
    print( sa, sa+3 );
}
