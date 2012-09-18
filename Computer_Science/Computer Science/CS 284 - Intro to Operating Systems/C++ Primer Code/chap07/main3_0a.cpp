// Section 7.3
// $ CC main3_0a.cpp swap.cpp 

/*
  Before swap():  i: 10   j: 20
  After swap():   i: 10   j: 20
*/

#include <iostream>
using std::cout;
using std::endl;

// definition in swap.cpp
void swap( int, int );

int main() {
        int i = 10;
        int j = 20;

        cout << "Before swap():\ti: "
             << i << "\tj: " << j << endl;

        swap( i, j );

        cout << "After swap():\ti: "
             << i << "\tj: " << j << endl;
        return 0;
}

