// Section 10.2
// $ CC inst.cpp 

/*

  !!ok: integer min() worked
  !!ok: double min() worked

*/

// definition of the function template min()
// with type parameter Type and nontype parameter size

template <typename Type, int size>
        Type min( Type (&r_array)[size] )
{
        Type min_val = r_array[0];
        for ( int i = 1; i < size; ++i )
                if ( r_array[i] < min_val )
                        min_val = r_array[i];

        return min_val;
}

// size not specified -- ok
// size = number of values in initializer list
int ia[] = { 10, 7, 14, 3, 25 };

double da[6] = { 10.2, 7.1, 14.5, 3.2, 25.0, 16.8 };

#include <iostream>
using std::cout;

int main()
{
        // instantiation of min() for an array of 5 ints
        // with Type => int, size => 5
        int i = min( ia );
        if ( i != 3 )
                cout << "??oops: integer min() failed\n";
        else cout << "!!ok: integer min() worked\n";

        // instantiation of min() for an array of 6 doubles
        // with Type => double, size => 6
        double d = min( da );
        if ( d != 3.2 )
                cout << "??oops: double min() failed\n";
        else cout << "!!ok: double min() worked\n";
        return 0;
}
