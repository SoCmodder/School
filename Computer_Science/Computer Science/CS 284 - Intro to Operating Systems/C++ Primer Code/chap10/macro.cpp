// Section 10.1
// $ CC macro.cpp 

/*

  elem_cnt : 5    expecting: 10

*/

#include <iostream>
using std::cout;
using std::endl;

#define min(a,b) ((a) < (b) ? (a) : (b))

const int size = 10;
int ia[size];

int main() {
        int elem_cnt = 0;
        int *p = &ia[0];

        // count the number of array elements
        while ( min(p++,&ia[size]) != &ia[size] )
                ++elem_cnt;

        cout << "elem_cnt : "   << elem_cnt
             << "\texpecting: " << size << endl;
        return 0;
}
