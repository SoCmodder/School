// #include <iostream>

#include <iostream.h>
#include <algorithm>
#include <vector>
#include <string>

/**
 ** These are Pooh's pals: Tigger Piglet Eeyore Rabbit
 **
 **/

string pooh_pals[] = {
	"Tigger", "Piglet", "Eeyore", "Rabbit" 
};

int main()
{
	vector< string > ppals( pooh_pals, pooh_pals+4 );

	vector< string >::iterator 
		iter = ppals.begin(),
		iter_end = ppals.end();

	cout << "These are Pooh's pals: ";

	// copies each element to cout ...
	ostream_iterator< string > output( cout, " " );
	copy( iter, iter_end, output );

	cout << endl;
}
