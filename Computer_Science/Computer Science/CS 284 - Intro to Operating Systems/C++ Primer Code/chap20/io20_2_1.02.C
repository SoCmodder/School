// #include <iostream>
// #include <iomanip>

#include <iostream.h>
#include <iomanip.h>

/*
 * the program generates the following unexpected results:
 *  $ a.out
 *  The winter of our discontent
 *
 *  The
 *  win
 *  ter
 *  of
 *  our
 *  dis
 *  con
 *  ten
 *  t
 *
 * The problem is that setw() is passed the size
 * of the character pointer rather than the size
 * of the character array to which it points.
 *
 * correct: while ( cin >> setw( bufSize ) >> pbuf )
 */

int main()
{
	const int bufSize = 24;
	char buf[ bufSize ];
	char *pbuf = buf;

	// each string greater than sizeof(char*)
	// is broken into two or more strings

	while ( cin >> setw( sizeof( pbuf )) >> pbuf )
 		cout << pbuf << endl;
}

