#ifndef ARRAY_RC_S_H
#define ARRAY_RC_S_H

#include "Array_S.C"
#include "Array_RC.C"

template <class elemType>
class Array_RC_S : public Array_RC<elemType>,
                   public Array_Sort<elemType>
{
public:
    Array_RC_S( int sz = Array<elemType>::DefaultArraySize )
              : Array<elemType>( sz )
              { clear_bit(); }

    Array_RC_S( const Array_RC_S &rca )
	      : Array<elemType>( rca )
              { sort( 0,Array<elemType>::_size-1 ); clear_bit(); }

    Array_RC_S( const elemType* arr, int sz )
 	      : Array<elemType>( arr, sz )
 	      { sort( 0,Array<elemType>::_size-1 ); clear_bit(); }

    elemType& operator[]( int index )
	{ 
		set_bit();
 	        return Array_RC<elemType>::operator[]( index );
        }

    elemType operator[]( int index ) const
	{ return Array_RC<elemType>::operator[]( index ); }
};

#endif

