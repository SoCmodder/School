// Section 10.7
// $ CC screen.cpp main7.cpp

/*
Output:

  ****
  ****
  ****
  ****
  @@@@@@
  @@@@@@
  ---
  ---
  ---
  ---
  ---
*/

#include "screen.h"

int main() {
	Screen s1 ( 4, 4, '*' );
	Screen s2 ( 2, 6, '@' );
	Screen s3 ( 5, 3, '-' );

	const int arrSize = 3;
	Screen *parray = new Screen[ arrSize ];

	parray[0] = s1;
	parray[1] = s2;
	parray[2] = s3;

	ScreenPtr parr( *parray, arrSize );

	for ( int ix = 0; ix < arrSize; ++ix )
	        parr++.display();

	delete parray;
        return 0;
}

