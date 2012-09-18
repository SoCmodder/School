// Section 15.6
// $ CC screen.cpp main6.cpp

/*
  Screen Object ( 2, 5 )

  Hello
  World
*/

#include <iostream>
using std::cout;

#include <string>
using std::string;

#include "screen.h"

void printScreen( ScreenPtr &ps )
{
        cout << "Screen Object ( "
             << ps->height() << ", "
             << ps->width() << " )\n\n";

        for ( int ix = 1; ix <= ps->height(); ++ix )
        {
                for ( int iy = 1; iy <= ps->width(); ++iy )
                        cout << ps->get( ix, iy );
                cout << "\n";
        }
}

int main() {
        Screen sobj( 2, 5 );
        string init( "HelloWorld" );
        ScreenPtr ps( sobj );

        // Set the content of the screen
        string::size_type initpos = 0;
        for ( int ix = 1; ix <= ps->height(); ++ix )
                for ( int iy = 1; iy <= ps->width(); ++iy )
                {
                        ps->move( ix, iy );
                        ps->set( init[ initpos++ ] );
                }

        // Print the content of the screen
        printScreen( ps );

        return 0;
}

