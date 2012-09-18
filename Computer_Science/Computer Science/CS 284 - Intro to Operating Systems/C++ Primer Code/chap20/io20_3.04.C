// #include <iostream>
#include <iostream.h>

/**
 **
 stanl@john:d.ch20 276 : a.out < moby_dick

 Line #1 Chars read: 45
 Call me Ishmael.  Some years ago, never mind

 Line #2 Chars read: 46
 how long precisely, having little or no money

 Line #3 Chars read: 48
 in my purse, and nothing particular to interest

 Line #4 Chars read: 51
 me on shore, I thought I would sail about a little

 Line #5 Chars read: 47
 and see the watery part of the world.  It is a

 Line #6 Chars read: 43
 way I have of driving off the spleen, and 

 Line #7 Chars read: 28
 regulating the circulation.

 Total lines read: 7
 Longest line read: 51
 **
 **/

int main() 
{
	const int lineSize = 1024;
	int lcnt = 0; // how many lines are read
	int max = -1; // size of longest line

	char inBuf[ lineSize ];

	// reads 1024 characters or up to newline
	while (cin.getline( inBuf, lineSize ))
	{
		// how many characters actually read
		int readin = cin.gcount();

		// statistics: line count, longest line
		++lcnt; 
		if ( readin > max ) 
     		     max = readin;

		cout << "Line #" << lcnt
		     << "\tChars read: " << readin << endl;

		cout.write( inBuf, readin).put('\n').put('\n');
	}

	cout << "Total lines read: " << lcnt << endl;
	cout << "Longest line read: " << max << endl;
}






