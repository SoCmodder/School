// #include <iostream>
// #include <cstring>

#include <iostream.h>
#include <string.h>

/**
 ** The length of ``ulysses'' is:   7
 ** The size of ``ulysses'' is:     8
 **
 **/

int main() 
{
    // output operators can be concatenated
    cout << "The length of ``ulysses'' is:\t"
         << strlen( "ulysses" ) << '\n';

    cout << "The size of ``ulysses'' is:\t"
         << sizeof( "ulysses" ) << endl;
}
