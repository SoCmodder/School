#ifndef ARRAYRC_H
#define ARRAYRC_H

#include "Array.h"

template <class elemType>
class ArrayRC : public virtual Array<elemType> {
public:
    ArrayRC( int sz = DefaultArraySize )
            : Array<elemType>( sz ) {}

    ArrayRC( const ArrayRC& r );
    ArrayRC( const elemType *ar, int sz );

    elemType  operator[]( int ix ) const;
    elemType& operator[]( int ix );
};

#endif
