// Section 13.3
// $ CC screen.cpp main3.cpp

/*
  Screen Object ( 3, 3 )

  abc
  def
  ghi
*/

#include <iostream>
using std::cout;

#include <string>
using std::string;

#include "screen.h"

int main() {
        Screen sobj(3,3); // constructor defined in Section 13.3.4
        string init("abcdefghi");

        cout << "Screen Object ( "
             << sobj.height() << ", "
             << sobj.width() << " )\n\n";

        // Set the content of the screen
        string::size_type initpos = 0;
        for ( int ix = 1; ix <= sobj.width(); ++ix )
                for ( int iy = 1; iy <= sobj.height(); ++iy )
                {
                        sobj.move( ix, iy );
                        sobj.set( init[ initpos++ ] );
                }

        // Print the content of the screen
        for ( int ix = 1; ix <= sobj.width(); ++ix )
        {
                for ( int iy = 1; iy <= sobj.height(); ++iy )
                        cout << sobj.get( ix, iy );
                cout << "\n";
        }

        return 0;
}
