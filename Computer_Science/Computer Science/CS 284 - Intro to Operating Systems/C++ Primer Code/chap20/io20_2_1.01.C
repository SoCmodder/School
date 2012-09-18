#include <iostream.h>
#include <string.h>

/** 
 **
	The number of words read is 65
	The longest word has a length of 10
	The longest word is creature,"
 **
 **/

int main() 
{
	const int bufSize = 24;
	char buf[ bufSize ], largest[ bufSize ];

	// hold statistics;
	int curLen, max = -1, cnt = 0;
	while ( cin >> buf ) 
	{
 		curLen = strlen( buf );
 		++cnt;

 		// new longest word? save it.
 		if ( curLen > max ) {
 			max = curLen;
 			strcpy( largest, buf );
 		}
	}

	cout << "The number of words read is "
	     << cnt << endl;

        cout << "The longest word has a length of "
	     << max << endl;

	cout << "The longest word is "
	     << largest << endl;
}	

