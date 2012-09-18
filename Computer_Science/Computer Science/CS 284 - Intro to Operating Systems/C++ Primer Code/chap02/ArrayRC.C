#include "ArrayRC.h"
#include "Array.C"

#include <assert.h>

template <class elemType>
ArrayRC<elemType>::
ArrayRC( const ArrayRC<elemType> &r )
       :  Array<elemType>( r ) {}

template <class elemType>
ArrayRC<elemType>::
ArrayRC( const elemType *ar, int sz )
       :  Array<elemType>( ar, sz ) {}

template <class elemType>
elemType&
ArrayRC<elemType>::
operator[]( int ix )
{
        assert( ix >= 0 && ix < Array<elemType>::_size );
        return _ia[ ix ];
}

template <class elemType>
elemType
ArrayRC<elemType>::
operator[]( int ix ) const
{
        assert( ix >= 0 && ix < Array<elemType>::_size );
        return _ia[ ix ];
}
