// #include <iostream>
// #include <iomanip>

#include <iostream.h>
#include <iomanip.h>

/*
 *  $ a.out
 *  The winter of our discontent
 *
 *  The
 *  winter
 *  of
 *  our
 *  discontent
 *  
 */

int main()
{
	const int bufSize = 24;
	char buf[ bufSize ];
	char *pbuf = buf;

	// each string greater than sizeof(bufsize)
	// is broken into two or more strings
 	while ( cin >> setw( bufSize ) >> pbuf )
 		cout << pbuf << endl;
}

