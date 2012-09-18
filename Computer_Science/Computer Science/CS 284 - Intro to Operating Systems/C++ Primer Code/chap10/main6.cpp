// Section 10.6
// $ CC main6.cpp

/*
  i: 10 p: world
*/

#include <iostream>
using std::cout;
using std::endl;

#include "max.cpp"

int main() {
        // call to instantiation: int max< int >( int, int );
        int i = max( 10, 5 );

        // call to explicit specialization:
        // const char* max< const char* >( const char*, const char* );
        const char *p = max( "hello", "world" );

        cout << "i: " << i << " p: " << p << endl;
        return 0;
}
