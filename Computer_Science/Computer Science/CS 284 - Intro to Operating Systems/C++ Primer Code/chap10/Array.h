#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
using std::ostream;
using std::cout;
using std::endl;

template <class elemType> class Array;
template <class elemType> ostream&
          operator<<( ostream &, Array<elemType> & );

template <class elemType>
class Array {
public:
    // explicit Array( int sz = DefaultArraySize )
    Array( int sz = DefaultArraySize )
         { init( 0, sz ); }

    Array( const elemType *ar, int sz )
         { init( ar, sz ); }

    Array( const Array &iA )
         { init( iA._ia, iA._size ); }

    virtual ~Array() { delete[] _ia; }

    Array& operator=( const Array & );
    int size() const { return _size; }

    virtual elemType& operator[]( int ix ) { return _ia[ix]; }
    virtual elemType  operator[]( int ix ) const { return _ia[ix]; }

    elemType at( int ix ) const { return _ia[ ix ]; }

    virtual ostream &print( ostream& os = cout ) const;
    virtual void grow();

protected:
    void init( const elemType*, int );

    // static const int DefaultArraySize = 12;
    static const int DefaultArraySize;
    int       _size;
    elemType *_ia;
};

#endif
