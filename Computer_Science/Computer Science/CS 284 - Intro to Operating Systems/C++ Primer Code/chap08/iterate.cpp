// Section 8.3.3
// $ CC iterate.cpp

/*
  value1: 0       	value2: 74924       	sum:    74924
  value1: 0       	value2: 68748          	sum:    68748
  value1: 0       	value2: 68756          	sum:    68756
  value1: 148620       	value2: 2350	 	sum:    150970
  value1: 2147479844 	value2: 671088640	sum:    -1476398812
  value1: 0      	value2: 68756       	sum:    68756

*/

#include <iostream>
using std::cout;

const int iterations = 2;

void iterate() {
        int value1, value2; // uninitialized
        static int depth;   // implicitly initialized to 0

        if ( depth < iterations )
                { ++depth; iterate(); }
        else depth = 0;

        cout << "\nvalue1:\t" << value1;
        cout << "\tvalue2:\t" << value2;
        cout << "\tsum:\t" << value1 + value2;
}

int main() {
        for ( int ix = 0; ix < iterations; ++ix ) iterate();
        return 0;
}

