#include <vector>

/***************
( 0 )( bot:  :top )
iStack::push( 2 )
iStack::push( 4 )
( 2 )( bot: 2 4  :top )
iStack::push( 6 )
iStack::push( 8 )
iStack::push( 10 )
( 5 )( bot: 2 4 6 8 10  :top )
iStack::pop(): 10
iStack::pop(): 8
( 3 )( bot: 2 4 6  :top )
iStack::push( 12 )
iStack::push( 14 )
( 5 )( bot: 2 4 6 12 14  :top )
iStack::push( 16 )
iStack::push( 18 )
iStack::push( 20 )
( 8 )( bot: 2 4 6 12 14 16 18 20  :top )
iStack::pop(): 20
iStack::pop(): 18
( 6 )( bot: 2 4 6 12 14 16  :top )
iStack::push( 22 )
iStack::push( 24 )
( 8 )( bot: 2 4 6 12 14 16 22 24  :top )
iStack::push( 26 )
iStack::push( 28 )
iStack::push( 30 )
( 11 )( bot: 2 4 6 12 14 16 22 24 26 28 30  :top )
iStack::pop(): 30
iStack::pop(): 28
( 9 )( bot: 2 4 6 12 14 16 22 24 26  :top )
iStack::push( 32 )
iStack::push( 34 )
( 11 )( bot: 2 4 6 12 14 16 22 24 26 32 34  :top )
iStack::push( 36 )
iStack::push( 38 )
iStack::push( 40 )
( 14 )( bot: 2 4 6 12 14 16 22 24 26 32 34 36 38 40  :top )
iStack::pop(): 40
iStack::pop(): 38
( 12 )( bot: 2 4 6 12 14 16 22 24 26 32 34 36  :top )
iStack::push( 42 )
iStack::push( 44 )
( 14 )( bot: 2 4 6 12 14 16 22 24 26 32 34 36 42 44  :top )
iStack::push( 46 )
iStack::push( 48 )
iStack::push( 50 )
( 17 )( bot: 2 4 6 12 14 16 22 24 26 32 34 36 42 44 46 48 50  :top )
iStack::pop(): 50
iStack::pop(): 48
( 15 )( bot: 2 4 6 12 14 16 22 24 26 32 34 36 42 44 46  :top )
****************/

class iStack {
public:
    iStack( int capacity )
  	    : _stack( capacity ), _top( 0 ) {};

    bool pop( int &value );
    bool push( int value );

    bool full();
    bool empty();
    void display();

    int size();

private:
    int _top;
    vector< int, allocator > _stack;
};

inline int  iStack::size()  { return _top; };
inline bool iStack::empty() { return _top ? false : true; }
inline bool iStack::full()  { return _top < _stack.size()-1 ? false : true; };

bool iStack::pop( int &top_value ) 
{ 
    if ( empty() )
         return false;

    top_value = _stack[ --_top ]; 

    cout << "iStack::pop(): " << top_value << endl;

    return true;
}

bool iStack::push( int value ) {

    cout << "iStack::push( " << value << " )\n";

    if ( full() )
         return false;

     _stack[ _top++ ] = value;
     return true;
};

void iStack::display() 
{
    cout << "( " << size() << " )( bot: ";

    for ( int ix = 0; ix < _top; ++ix )
 	  cout << _stack[ ix ] << " ";

    cout << " :top )\n";
};

// #include <iostream>
#include <iostream.h>

int main() 
{
    iStack stack( 32 );

    stack.display();
    for ( int ix = 1; ix < 51; ++ix ) 
    {
        if ( ix%2 == 0 )
             stack.push( ix );

        if ( ix%5 == 0 )
             stack.display();

        if ( ix%10  == 0) {
             int dummy;
             stack.pop( dummy ); stack.pop( dummy );
             stack.display();
        }
    }
}
