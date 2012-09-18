#include <iterator>
#include <algorithm>
#include <iostream.h>
// #include <iostream>

/**
 **
 stanl@john:d.12 338 : xsh32 ch12.4.02.c
 stanl@john:d.12 339 : a.out
 0 1 1 2 3 5 8 
 0 1 1 2 3 5 8 stanl@john:d.12 340 : 
 **
 **/

int main()
{
	copy( istream_iterator< int >( cin ),
 		istream_iterator< int >(),
 		ostream_iterator< int >( cout, " " ));
}
