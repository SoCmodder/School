// version 1: incorrect
// #include <iostream>
// #include <fstream>

#include <iostream.h>
#include <fstream.h>

/**
 **
 stanl@john:d.ch20 268 : cat moby_dick.copy

 Call me Ishmael.  Some years ago, never mind
 how long precisely, having little or no money
 in my purse, and nothing particular to interest
 me on shore, I thought I would sail about a little
 and see the watery part of the world.  It is a
 way I have of driving off the spleen, and 
 regulating the circulation.

 stanl@john:d.ch20 269 : a.out
 [ 0 ]

 stanl@john:d.ch20 270 : cat moby_dick.copy

 Call me Ishmael.  Some years ago, never mind
 how long precisely, having little or no money
 in my purse, and nothing particular to interest
 me on shore, I thought I would sail about a little
 and see the watery part of the world.  It is a
 way I have of driving off the spleen, and 
 regulating the circulation.
 0
 **
 **/

main() {
    // open in both input and append mode
    // ios is preStandard class name
    // fstream inOut( "moby_dick.copy", ios_base::in|ios_base::app );
    fstream inOut( "moby_dick.copy", ios::in|ios::app );

    if ( ! inOut ) {
 	 cerr << "oops! unable to open file ``copy.out''\n";
	 return -1;
    }

    int cnt = 0;   // byte count
    char ch;

    while ( inOut.get( ch )) 
    {
        cout.put( ch ); // echo on terminal
        ++cnt;

        if ( ch == '\n' ) {
            inOut << cnt ;
            inOut.put( ' ' ); // blank space
        }
    }

    // write out final byte count
    inOut << cnt << endl;
    cout << "[ " << cnt << " ]" << endl;
    return 0;
}
