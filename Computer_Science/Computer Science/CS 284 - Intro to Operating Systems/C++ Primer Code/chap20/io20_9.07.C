// #include <iostream>
// #include <iomanip>

#include <iostream.h>
#include <iomanip.h>

/**
 ival:           16
 dval:      3.14159
 **
 **/

int main()
{
	int ival = 16;
	double dval = 3.14159;
	
	cout << "ival: " << setw(12) << ival << '\n'
	     << "dval: " << setw(12) << dval << '\n';
}

