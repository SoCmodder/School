// Section 7.3
// $ CC main3c.cpp rswap.cpp

/*
  Before rswap(): i: 10   j: 20
  After rswap():  i: 20   j: 10
*/

#include <iostream>
using std::cout;
using std::endl;

// definition in rswap.cpp
void rswap( int&, int& );

int main() {
        int i = 10;
        int j = 20;

        cout << "Before rswap():\ti: "
             << i << "\tj: " << j << endl;

        rswap( i, j );

        cout << "After rswap():\ti: "
             << i << "\tj: " << j << endl;
        return 0;
}

