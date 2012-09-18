#ifndef IntArrayRC_H
#define IntArrayRC_H

#include "IntArray.h"
#include <assert.h>
// #include <cassert>

class IntArrayRC : public IntArray {
public:
   	IntArrayRC( int sz = DefaultArraySize );
   	IntArrayRC( const int *array, int array_size );
   	IntArrayRC( const IntArrayRC &rhs );

   	virtual int& operator[]( int ) const;

private:

   	void check_range( int ix ) const {
 	     assert( ix >= 0  && ix < _size );
	}
};

inline int&
IntArrayRC::operator[]( int index ) const
{
   	check_range( index );
   	return _ia[ index ];
}

inline IntArrayRC::IntArrayRC( int sz)
   	: IntArray( sz ) {}

inline IntArrayRC::IntArrayRC( const int *iar, int sz )
   	: IntArray( iar, sz ) {}


#endif

