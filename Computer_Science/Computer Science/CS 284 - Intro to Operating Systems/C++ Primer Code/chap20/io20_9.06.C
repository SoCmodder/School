// #include <iostream>
// #include <iomanip>
// #include <cmath>

#include <iostream.h>
#include <iomanip.h>
#include <math.h>

/**
 ** note: must include the C standard math library
 **       unix: CC io20_9.06.c -lm
 **
 Precision: 6
 1.41421

 Precision: 12
 1.41421356237

 Precision: 3
 1.41
 **
 **/

int main()
{
	cout << "Precision: "
             << cout.precision() << '\n'
             << sqrt(2.0) << '\n';

        cout.precision(12);

	cout << "\nPrecision: "
	     << cout.precision() << '\n'
             << sqrt(2.0) << '\n';

	cout << "\nPrecision: "  << setprecision(3)
	     << cout.precision() << '\n'
	     << sqrt(2.0) << endl;

	return 0;
}

