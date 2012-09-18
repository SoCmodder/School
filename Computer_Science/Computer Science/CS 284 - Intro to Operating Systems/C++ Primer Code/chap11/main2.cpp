// $ CC iStack.cpp main2.cpp

#include <iostream>
#include <iostream>
using std::cerr;

#include "iStack.h"

/*
  ( 0 )( bot:  :top )
  iStack::push( 3 )
  ( 1 )( bot: 3  :top )
  iStack::push( 6 )
  ( 2 )( bot: 3 6  :top )
  iStack::push( 9 )
  iStack::pop(): 9
  ( 2 )( bot: 3 6  :top )
  iStack::push( 12 )
  ( 3 )( bot: 3 6 12  :top )
  iStack::push( 15 )
  ( 4 )( bot: 3 6 12 15  :top )
  iStack::push( 18 )
  ( 5 )( bot: 3 6 12 15 18  :top )
  iStack::pop(): 18
  ( 4 )( bot: 3 6 12 15  :top )
  iStack::push( 21 )
  iStack::push( 24 )
  trying to push value 24 on a full stack
*/

int main() {
        iStack stack( 6 );

	try {
	        stack.display();
        	for ( int ix = 1; ix < 51; ++ix )
        	{
                	if ( ix % 3 == 0 )
                        	stack.push( ix );

	                if ( ix % 4 == 0 )
	                        stack.display();

	                if ( ix % 10  == 0) {
	                        int dummy;
	                        stack.pop( dummy );
	                        stack.display();
	                }
	        }
	}
	catch ( pushOnFull eObj ) {
	        cerr << "trying to push value " << eObj.value()
	             << " on a full stack\n";
	}
	catch ( popOnEmpty ) {
	        cerr << "trying to pop a value on an empty stack\n";
	}

        return 0;
}
