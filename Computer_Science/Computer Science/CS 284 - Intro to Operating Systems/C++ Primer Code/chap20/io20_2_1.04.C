// #include <iostream>

#include <iostream.h>
#include <string>

/**
 **
 stanl@john: d.ch20 261 : a.out < alice_emma

 The number of words read is 65
 The longest word has a length of 10
 The longest word is creature,"

 **
 **/

int main()
{
	string buf, largest;

	// hold statistics;
	int curLen,   // length of current word
	    max = -1, // maximum word length
	    cnt = 0;  // count of words read

	while ( cin >> buf ) 
	{
 		curLen = buf.size();
 		++cnt;

 		// new longest word? save it.
 		if ( curLen > max ) 
		{
 			max = curLen;
 			largest = buf;
 		}
	}

	cout << "The number of words read is " << cnt << endl;
	cout << "The longest word has a length of " << max << endl;
	cout << "The longest word is " << largest << endl;
}
