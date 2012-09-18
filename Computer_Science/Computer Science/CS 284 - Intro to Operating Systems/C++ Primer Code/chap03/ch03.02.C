// #include <iostream>
#include <iostream.h>

/**
 ** 2 raised to the power of 10: 	1024
 **/
 

int main()
{
	int value = 2;
	int pow  = 10;

	cout << value << " raised to the power of "
     	     << pow << ": \t";

	int res = 1; 

	// loop control statement: 
	// repeat calculation of res
	// until cnt is greater than pow
	for ( int cnt=1; cnt <= pow; ++cnt )
 	      res = res * value;

	cout << res << endl;
}
