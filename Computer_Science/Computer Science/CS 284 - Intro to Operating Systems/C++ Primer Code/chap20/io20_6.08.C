// version 2: corrected
// #include <iostream>
// #include <fstream>

#include <iostream.h>
#include <fstream.h>

/**
 **
 ** note: use of preStandard iostream library
 **       

 stanl@john:d.ch20 275 : a.out

 Call me Ishmael.  Some years ago, never mind
 how long precisely, having little or no money
 in my purse, and nothing particular to interest
 me on shore, I thought I would sail about a little
 and see the watery part of the world.  It is a
 way I have of driving off the spleen, and 
 regulating the circulation.
 45 91 139 190 237 280 308 [ 334 ]

 stanl@john:d.ch20 276 : cat moby_dick.copy

 Call me Ishmael.  Some years ago, never mind
 how long precisely, having little or no money
 in my purse, and nothing particular to interest
 me on shore, I thought I would sail about a little
 and see the watery part of the world.  It is a
 way I have of driving off the spleen, and 
 regulating the circulation.
 45 91 139 190 237 280 308 334

 **
 **/

int main()
{
    // fstream inOut( "moby_dick.copy", ios_base::in|ios_base::app );
    fstream inOut( "moby_dick.copy", ios::in|ios::app );

    if ( ! inOut ) {
         cerr << "oops! unable to open file ``copy.out''\n";
         return -1;
    }

    int cnt=0;
    char ch;
    inOut.seekg(0);

    while ( inOut.get( ch ))
    {
        cout.put( ch );
        cnt++;

        if ( ch == '\n' )
        {
            // mark current position
            // ios_base::pos_type mark = inOut.tellg();
	    // preStandard equivalent
            streampos mark = inOut.tellg();
            inOut << cnt << ' ';
            inOut.seekg( mark ); // restore position
        }
    }

    inOut.clear();
    inOut << cnt << endl;
    cout << "[ " << cnt << " ]\n";

    return 0;
}





