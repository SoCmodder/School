// #include <iostream>
#include <iostream.h>

/** 
 ** generates:

 stanl@john:d.ch20 313 : a.out < alice_emma

 characters actually read: 52
 characters actually read: 60
 characters actually read: 66
 characters actually read: 63
 characters actually read: 61
 characters actually read: 43

 ** let's stress the maximum:

 stanl@john:d.ch20 314 : a.out < xxx

 characters actually read: 1023
 characters actually read: 528
 characters actually read: 52
 characters actually read: 60
 characters actually read: 66
 characters actually read: 63
 characters actually read: 61
 characters actually read: 43
 **
 **/

int main() 
{
	const int max_line = 1024;
	char line[ max_line ];

	while ( cin.get( line, max_line )) 
	{
		// maximum read is max_line - 1 to allow for null
		int get_count = cin.gcount();
		cout << "characters actually read: " 
		     << get_count << endl;

		// do something with line

		// if we encountered a newline, 
		// discard it before we read next line
		if ( get_count < max_line-1 )
     			cin.ignore();
	}
}

