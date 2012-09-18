// #include <iostream>
#include <iostream.h>

/**
 **
 ** ival: 16 oct set: 020
 ** dval: 16 hex set: 16
 ** ival: 0x10 dec set: 16
 **
 **/

int main()
{
	int ival = 16;
	double dval = 16.0;
	
	// cout << showbase;
	// this is preStandard equivalent support
	cout.setf( ios::showbase );
	cout << "ival: " << ival  << " oct set: " << oct << ival << "\n";
	cout << "dval: " << dval  << " hex set: " << hex << dval << "\n";
	cout << "ival: " << ival  << " dec set: " << dec << ival << "\n";
}

