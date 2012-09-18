#ifndef ARRAY_RC_H
#define ARRAY_RC_H

#include "Array.h"

template <class elemType>
class Array_RC : public virtual Array<elemType> {
public:
    Array_RC( int sz = DefaultArraySize )
            : Array<elemType>( sz ) {}

    Array_RC( const Array_RC& r );
    Array_RC( const elemType *ar, int sz );

    elemType  operator[]( int ix ) const;
    elemType& operator[]( int ix );
};

#endif
