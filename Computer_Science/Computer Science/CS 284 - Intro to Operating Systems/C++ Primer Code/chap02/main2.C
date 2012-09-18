// #include <iostream>
#include <iostream.h>
#include "Array.C"

/**
 **
 [ 0 ]  ia: 0    ca: a   da: 0
 [ 1 ]  ia: 1    ca: b   da: 1.75
 [ 2 ]  ia: 2    ca: c   da: 3.5
 [ 3 ]  ia: 3    ca: d   da: 5.25
 **
 **/

int main()
{
 	const int array_size = 4;

 	// elemType becomes int
 	Array<int> ia(array_size);

 	// elemType becomes double
 	Array<double> da(array_size);

 	// elemType becomes char
 	Array<char> ca(array_size);

    	int ix;

    	for ( ix = 0; ix < array_size; ++ix ) {
        	ia[ix] = ix;
        	da[ix] = ix * 1.75;
        	ca[ix] = ix + 'a';
    	}

    	for ( ix = 0; ix < array_size; ++ix )
        	cout << "[ " << ix << " ]  ia: "  << ia[ix]
           		<< "\tca: " << ca[ix]
           		<< "\tda: " << da[ix] << endl;

 	return 0;
}

