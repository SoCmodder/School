#include "Array_RC.h"
#include "Array.C"

#include <assert.h>

template <class elemType>
Array_RC<elemType>::
Array_RC( const Array_RC<elemType> &r )
       :  Array<elemType>( r ) {}

template <class elemType>
Array_RC<elemType>::
Array_RC( const elemType *ar, int sz )
       :  Array<elemType>( ar, sz ) {}

template <class elemType>
elemType&
Array_RC<elemType>::
operator[]( int ix )
{
        assert( ix >= 0 && ix < Array<elemType>::_size );
        return _ia[ ix ];
}

template <class elemType>
elemType
Array_RC<elemType>::
operator[]( int ix ) const
{
        assert( ix >= 0 && ix < Array<elemType>::_size );
        return _ia[ ix ];
}
