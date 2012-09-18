#ifndef SCREEN_H
#define SCREEN_H

#include <string>
using std::string;

#include <cstddef>

//-------------
// Screen class
//-------------

class Screen {
public:
	enum CursorMovements {
	        HOME, FORWARD, BACK, UP, DOWN, END
	};
	typedef Screen& (Screen::*Action)();

	Screen( int hi = 8, int wid = 40, char bkground = '#' );
	Screen( const Screen & );

	int height();
        int width();
        Screen& home();
        Screen& end();
        Screen& move( int, int );
	Screen& move( CursorMovements );
	Screen& clear( char = '#' );
        char get();
        char get( int, int );
        Screen& set( char ch );
        Screen& set( const string &s );
        Screen& forward();
        Screen& back();
        Screen& up();
        Screen& down();
	Screen& repeat( Action = &Screen::forward, int = 1 );
        Screen& reSize( int, int, char = '#' );
	Screen& display();
        bool checkRange( int, int );

	void *operator new( size_t );
	void operator delete( void *, size_t ); 
private:
	int remainingSpace();
        int row();

	static Action Menu[6]; 

        string                     _screen;   // string( _height * _width )
        mutable string::size_type  _cursor;   // current Screen position
        short                      _height;   // number of Screen rows
        short                      _width;    // number of Screen columns

	Screen *next;
        static Screen *freeStore;
        static const int screenChunk;
};

inline Screen::Screen( int hi, int wid, char bk ) :
  _height( hi ),  // initializes _height with hi
  _width( wid ),  // initializes _width with wid
  _cursor ( 0 ),  // initializes _cursor to 0
  _screen( hi * wid, bk ) // size of _screen is hi * wid
                          // all positions initialized with
                          // character value of bk
  { /* all the work is done with the member initialization list */ }

inline int Screen::height() { return _height; }

inline int Screen::width() { return _width; }

inline Screen& Screen::home()
  { 
    _cursor = 0;
    return *this;
  }

inline Screen& Screen::end()
  {
    _cursor = _width * _height - 1;
    return *this;
  }

inline char Screen::get() { return _screen[_cursor]; }

inline int Screen::remainingSpace()
  { // current position is no longer remaining
    int sz = _width * _height;
    return( sz - _cursor );
  }

inline int Screen::row()
{ // return current row
        return ( _cursor + _width ) / _width;
}

//----------------
// ScreenPtr class
//----------------

class ScreenPtr {
public:
	ScreenPtr( Screen &s , int arraySize = 0 )
                 : ptr( &s ), size ( arraySize ), offset( 0 ) { }

        Screen& operator*()  { return *ptr; }
        Screen* operator->() { return ptr; }
	Screen& operator++(); // prefix operators
        Screen& operator--();
        Screen& operator++(int); // postfix operators
        Screen& operator--(int);
private:
        Screen *ptr;
        int size;    // size of the array; zero if single object
        int offset;  // offset of ptr within the array
};
#endif
