#ifndef ARRAY_S_H_
#define ARRAY_S_H_

#include "Array.h"

template <class elemType>
class Array_Sort : public virtual Array<elemType> {
protected:
    void set_bit()   { dirty_bit = true; }
    void clear_bit() { dirty_bit = false; }

    void check_bit() {
         if ( dirty_bit ) {
              sort( 0, Array<elemType>::_size-1 );
              clear_bit();
         }
    }

public:
    Array_Sort( const Array_Sort& );
    Array_Sort( int sz = Array<elemType>::DefaultArraySize )
              : Array<elemType>( sz ) { clear_bit();  }

    Array_Sort( const elemType* arr, int sz )
              : Array<elemType>( arr, sz )
              { sort( 0,Array<elemType>::_size-1 ); clear_bit(); }

    elemType& operator[]( int ix ) 
	      { set_bit(); return _ia[ ix ]; }

    elemType  operator[]( int ix ) const
	      { return Array<elemType>::operator[](ix); }

    ostream& print( ostream& os = cout ) const { 
		((Array_Sort*)this)->check_bit(); 
		return Array<elemType>::print( os ); 
    }

    elemType min() { check_bit(); return _ia[ 0 ]; }
    elemType max() { check_bit(); return _ia[ Array<elemType>::_size-1 ]; }

    bool is_dirty() const { return dirty_bit; }
    int  find( const elemType& );
    void grow();

protected:
    // mutable bool dirty_bit;
    mutable bool dirty_bit;
};
#endif

