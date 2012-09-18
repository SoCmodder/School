// Section 7.3
// $ CC main3_0b.cpp pswap.cpp

/*
  Before pswap(): i: 10   j: 20
  After pswap():  i: 20   j: 10
*/

#include <iostream>
using std::cout;
using std::endl;

// definition in pswap.cpp
void pswap( int *, int * );

int main() {
        int i = 10;
        int j = 20;

        cout << "Before pswap():\ti: "
             << i << "\tj: " << j << endl;

        pswap( &i, &j );

        cout << "After pswap():\ti: "
             << i << "\tj: " << j << endl;
        return 0;
}

