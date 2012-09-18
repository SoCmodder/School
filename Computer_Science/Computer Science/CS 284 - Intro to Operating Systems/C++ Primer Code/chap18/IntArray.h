#ifndef INT_ARRAY_H
#define INT_ARRAY_H

// #include <iostream>
#include <iostream.h>

class IntArray;
ostream& operator<<( ostream &, IntArray& );

class IntArray {
public:
    // explicit IntArray( int sz = DefaultArraySize )
    IntArray( int sz = DefaultArraySize ) { init( 0, sz );  }
    IntArray( const int *ar, int sz )     { init( ar, sz ); }
    IntArray( const IntArray &iA ) { init( iA._ia, iA._size ); }

    ~IntArray() { delete[] _ia; }

    IntArray & operator=( const IntArray& );
    int size() const { return _size; }

    int& operator[]( int ix ) const { return _ia[ix]; }

    ostream &print( ostream& os = cout ) const;
    void grow();
    void sort( int, int );
    int find( int );

    int min();
    int max();

protected:
    void init( const int*, int );
    void swap( int, int );

    // static const int DefaultArraySize = 12;
    static const int DefaultArraySize;
    int       _size;
    int	     *_ia;
};

#endif
