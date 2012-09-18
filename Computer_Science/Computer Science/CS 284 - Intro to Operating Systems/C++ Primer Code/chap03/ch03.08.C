// #include <iostream>
#include <iostream.h>

/**
 ** ia[ 9 ] = { 0 1 1 2 3 5 8 13 21  }
 **/

int main()
{
    int ia[ 9 ] = { 0, 1, 1, 2, 3, 5, 8, 13, 21 };
    int *pbegin = ia;
    int *pend   = ia+9;

    // iterate over the 9 elements
    cout << "ia[ 9 ] = { ";

    while ( pbegin != pend ) 
            cout << *pbegin++ << ' ';

    cout << " }\n";
}
