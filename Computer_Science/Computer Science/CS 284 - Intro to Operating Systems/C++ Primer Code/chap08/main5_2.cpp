// Section 8.5.2
// $ CC fibon.cpp main5_2.cpp

/*

Fibonacci Series: 16
0 1 1 2 3 5 8 13 21 34 55 89 
144 233 377 610

*/

#include <iostream>
using std::cout;

// Defined in fibon.C
void fibonacci( int );

int main() {
        cout << "Fibonacci Series: 16\n";
        fibonacci( 16 );
        return 0;
}
