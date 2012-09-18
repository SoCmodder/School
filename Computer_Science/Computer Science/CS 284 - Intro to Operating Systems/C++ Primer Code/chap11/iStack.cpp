#include <iostream>
using std::cout;
using std::endl;

#include "iStack.h"

void iStack::pop( int &top_value ) throw( popOnEmpty )
{
        if ( empty() )
                throw popOnEmpty();

        top_value = _stack[ --_top ];

        cout << "iStack::pop(): " << top_value << endl;
}

void iStack::push( int value ) throw( pushOnFull )
{
        cout << "iStack::push( " << value << " )\n";

        if ( full() )
                throw pushOnFull( value );

        _stack[ _top++ ] = value;
}

void iStack::display()
{
    cout << "( " << size() << " )( bot: ";

    for ( int ix = 0; ix < _top; ++ix )
          cout << _stack[ ix ] << " ";

    cout << " :top )\n";
}

