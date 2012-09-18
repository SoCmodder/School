// Section 8.3.3
// $ CC tracegcd.C main3_3.C

/*
  depth #1
  depth #2
  depth #3
  depth #4
  gcd of (15,123): 3
*/

#include <iostream>
using std::cout;
using std::endl;

// defined in tracegcd.C
extern int traceGcd(int, int);

int main() {
        int rslt = traceGcd( 15, 123 );
        cout << "gcd of (15,123): " << rslt << endl;
        return 0;
}
