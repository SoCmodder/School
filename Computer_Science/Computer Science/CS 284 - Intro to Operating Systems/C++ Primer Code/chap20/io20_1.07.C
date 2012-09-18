// #include <iostream>
#include <iostream.h>

/**
 ** The larger of 10, 20 is 0
 **
 **/

inline void
max_out( int val1, int val2 ) 
{
    // oops: incorrect precedence ...
    cout << ( val1 > val2 ) 
            ? val1 : val2;
}

int main()
{
    int ix = 10, jx = 20;

    cout << "The larger of " << ix
         << ", " << jx << " is ";

    max_out( ix, jx );

    cout << endl;
}
