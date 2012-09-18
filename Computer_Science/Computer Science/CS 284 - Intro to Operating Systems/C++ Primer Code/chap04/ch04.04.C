// #include <iostream>
// #include <cstddef>

#include <string>
#include <iostream.h>
#include <stddef.h>

/*****
  pi: 4 *pi: 4
  st1: 12 st2: 12 ps: 4 *ps: 12
  short :	2
  short* :	4
  short& :	2
  short[3] :	6
*****/

int main()
{
    size_t ia;
    ia = sizeof( ia );     // ok
    ia = sizeof ia;        // ok
    // ia = sizeof int;    // error
    ia = sizeof( int );    // ok

    int *pi = new int[ 12 ];
    cout << "pi: " << sizeof( pi )
         << " *pi: " << sizeof( *pi )
         << endl;

    // a string's size is independent of
    // of the length of the string it addresses

    string st1( "foobar" );
    string st2( "a might oak" );
    string *ps = &st1;

    cout << "st1: " << sizeof( st1 )
         << " st2: " << sizeof( st2 )
         << " ps: " << sizeof( ps )
         << " *ps: " << sizeof( *ps )
         << endl;

    cout << "short :\t"    << sizeof(short)    << endl;
    cout << "short* :\t"   << sizeof(short*)   << endl;
    cout << "short& :\t"   << sizeof(short&)   << endl;
    cout << "short[3] :\t" << sizeof(short[3]) << endl;
}
