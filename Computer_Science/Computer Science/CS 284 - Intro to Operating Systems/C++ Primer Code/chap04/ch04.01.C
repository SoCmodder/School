// #include <iostream>
#include <iostream.h>

/**
 ** byte_value: 0
 **/

int main() {
	char byte_value = 32;
	int ival = 8;

	// overflow of byte_valueís available memory
	byte_value = ival * byte_value;
	cout << "byte_value: " 
	     << static_cast<int>(byte_value)
	     << endl;
}
