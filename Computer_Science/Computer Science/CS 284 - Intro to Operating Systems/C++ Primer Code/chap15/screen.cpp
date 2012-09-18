#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

#include "screen.h"

// --------------------------
// Screen static data members
// --------------------------

Screen::Action Screen::Menu[] = {
        &Screen::home,
        &Screen::forward,
        &Screen::back,
        &Screen::up,
        &Screen::down,
        &Screen::end
};

Screen *Screen::freeStore = 0;
const int Screen::screenChunk = 24;

// -----------------------
// Screen member functions
// -----------------------

Screen::Screen( const Screen &sobj )
{
        // if this Screen object and sobj are the same object,
        // no copy necessary
        if ( this != &sobj )
        {
                _height = sobj._height;
                _width = sobj._width;
                _cursor = 0;

                // creates a new string;
                // its content is the same as sobj._screen
                _screen = sobj._screen;
        }
}

Screen& Screen::move( int r, int c )
{ // move _cursor to absolute position
        if ( checkRange( r, c ) ) // valid screen position?
        {
                int row = (r-1) * _width; // row location
                _cursor = row + c - 1;
        }

	return *this;
}

Screen& Screen::move( CursorMovements cm )
{
        ( this->*Menu[ cm ] )();
        return *this;
}

Screen& Screen::clear( char bkground )
{ // reset the cursor and clear the screen

        _cursor = 0;
        _screen.assign(       // assign the string
                _screen.size(),    // with size() characters
                bkground           // of value bkground
        );

        // return the object for which the function was invoked
        return *this;
}

char Screen::get( int r, int c )
{
        move( r, c ); // position _cursor
        return get(); // the other get() member function
}

Screen& Screen::set( char ch ) 
{
        if ( ch == '\0' )
                cerr << "Screen: warning: "
                     << "null character (ignored).\n";
        else _screen[_cursor] = ch;

        return *this;
}

Screen& Screen::set( const string &s )
{ // write string beginning at current _cursor position

        int space = remainingSpace();
        int len = s.size();
        if ( space < len ) {
                cerr << "Screen: warning: truncation: "
                     << "space: " << space
                     << "string length: " << len << endl;
                len = space;
        }

        _screen.replace( _cursor, len, s );
        _cursor += len - 1;

        return *this;
}

Screen& Screen::forward()
{ // advance _cursor one screen element

        ++_cursor;

        // check for end of screen; wrap around
        if ( _cursor == _screen.size() )
                home();

        return *this;
}

Screen& Screen::back()
{ // move _cursor backward one screen element

        // check for top of screen; wrap around
        if ( _cursor == 0 )
                end();
        else
                --_cursor;

        return *this;
}

const char BELL = '\007';

Screen& Screen::up()
{ // move _cursor up one row of screen
  // do not wrap around; rather, ring bell

        if ( row() == 1 ) // at top?
                cout << BELL << endl;
        else
                _cursor -= _width;

        return *this;
}

Screen& Screen::down()
{
        if ( row() == _height ) // at bottom?
                cout << BELL << endl;
        else
                _cursor += _width;

        return *this;
}

Screen& Screen::repeat( Screen::Action op, int times )
{
        for ( int i = 0; i < times; ++i )
                (this->*op)();
        return *this;
}

Screen& Screen::reSize( int h, int w, char bkground )
{ // resize a screen to height h and width w

        // remember the content of the screen
        string local(_screen);

        // replaces the string to which _screen refers
        _screen.assign(     // assign the string
                h * w,           // with h * w characters
                bkground         // of value bkground
        );

        typedef string::size_type idx_type;
        idx_type local_pos = 0;

        // copy content of old screen into the new one
        for ( idx_type ix = 0; ix < _height; ++ix )
        { // for each row

                idx_type offset = w * ix; // row position
                for ( idx_type iy = 0; iy < _width; ++iy )
                        // for each column, assign the old value
                        _screen[ offset + iy ] = local[ local_pos++ ];
        }

        _height = h;
        _width = w;
        // _cursor remains unchanged

        return *this;
}

Screen& Screen::display()
{
        typedef string::size_type idx_type;

        for ( idx_type ix = 0; ix < _height; ++ix )
        { // for each row

                idx_type offset = _width * ix; // row position

                for ( idx_type iy = 0; iy < _width; ++iy )
                        // for each column, write element
                        cout << _screen[ offset + iy ];

                cout << endl;
        }
        return *this;
}

bool Screen::checkRange( int row, int col )
{ // validate coordinates
        if ( row < 1 || row > _height ||
             col < 1 || col > _width ) {
                cerr << "Screen coordinates ( "
                     << row << ", " << col
                     << " ) out of bounds.\n";
                return false;
        }
        return true;
}

void *Screen::operator new( size_t size )
{
        Screen *p;

        if ( !freeStore ) {
                // linked list empty: grab a chunk
                // this call is to the global new
                size_t chunk = screenChunk * size;
                freeStore = p =
                        reinterpret_cast< Screen* >( new char[ chunk ] );

                // now thread the memory allocated
                for ( ;
                      p != &freeStore[ screenChunk - 1 ];
                      ++p )
                        p->next = p+1;
                p->next = 0;
        }

        p = freeStore;
        freeStore = freeStore->next;
        return p;
}

void Screen::operator delete( void *p, size_t )
{
        // insert the "deleted" object back
        // into the free list

        ( static_cast< Screen* >( p ) )->next = freeStore;
        freeStore = static_cast< Screen* >( p );
}

// --------------------------
// ScreenPtr member functions
// --------------------------

Screen& ScreenPtr::operator++()
{
        if ( size == 0 ) {
                cerr << "cannot increment pointer to single object\n";
                return *ptr;
        }
        if ( offset >= size - 1 ) {
                cerr << "already at the end of the array\n";
                return *ptr;
        }

        ++offset;
        return *++ptr;
}

Screen& ScreenPtr::operator--()
{
        if ( size == 0 ) {
                cerr << "cannot decrement pointer to single object\n";
                return *ptr;
        }
        if ( offset <= 0 ) {
                cerr << "already at the beginning of the array\n";
                return *ptr;
        }

        --offset;
        return *--ptr;
}

Screen& ScreenPtr::operator++(int)
{
        if ( size == 0 ) {
                cerr << "cannot increment pointer to single object\n";
                return *ptr;
        }
        if ( offset == size ) {
                cerr << "already one past the end of the array\n";
                return *ptr;
        }

        ++offset;
        return *ptr++;
}

Screen& ScreenPtr::operator--(int)
{
        if ( size == 0 ) {
                cerr << "cannot decrement pointer to single object\n";
                return *ptr;
        }
        if ( offset == -1 ) {
                cerr << "already one before the beginning of the array\n";
                return *ptr;
        }

        --offset;
        return *ptr--;
}

