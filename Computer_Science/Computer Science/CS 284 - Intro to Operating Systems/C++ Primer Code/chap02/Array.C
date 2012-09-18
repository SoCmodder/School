#ifndef ARRAY_C
#define ARRAY_C

#include <assert.h>
#include "Array.h"

template <class elemType>
const int Array<elemType>::DefaultArraySize = 12;

template <class elemType>
    void Array<elemType>::init( const elemType *array, int sz )
{
    if ( ! array ) { _size = 0; _ia = 0; }
    if ( sz < 1 ) sz = 1;

    _size = sz;
    _ia = new elemType[ _size ];

    if ( ! array ) return;

    for ( int ix = 0; ix < _size; ++ix )
	  _ia[ ix ] = array[ ix ];
}

template <class elemType> Array<elemType>&
    Array<elemType>::operator=( const Array<elemType> &iA )
{
    if ( this == &iA )
         return *this;

    delete[] _ia;
    init( iA._ia, iA._size );
    return *this;
}

template <class elemType> ostream&
    operator<<( ostream &os, Array<elemType> &ar )
{
    return ar.print( os );
}

template <class elemType>
    ostream& Array<elemType>::print( ostream &os ) const
{
    const int lineLength = 12;
    os << "( " << _size << " )< ";

    for ( int ix = 0; ix < _size; ++ix )
    {
          if ( ix % lineLength == 0 && ix )
               os << "\n\t";

          os << _ia[ ix ];
          // don't generate comma for last item on line
          // nor for the last element of the array
          if ( ix % lineLength != lineLength-1 && ix != _size-1 )
               os << ", ";
    }

    os << " >\n";
    return os;
}

template <class elemType>
    void Array<elemType>::grow()
{ 
    elemType *oldia = _ia;
    int oldSize = _size;

    _size = oldSize + oldSize/2 + 1;
    _ia   = new elemType[_size];

    int ix;
    for ( ix = 0; ix < oldSize; ++ix)
          _ia[ix] = oldia[ix];

    for ( ; ix < _size; ++ix )
	  _ia[ix] = elemType();

    delete[] oldia;
}

template <class elemType>
    elemType Array<elemType>::min( )
{
    assert( _ia != 0 );
    elemType min_val = _ia[0];

    for ( int ix = 1; ix < _size; ++ix )
          if ( _ia[ix] < min_val )
               min_val = _ia[ix];

    return min_val;
}

template <class elemType>
    elemType Array<elemType>::max()
{
    assert( _ia != 0 );
    elemType max_val = _ia[0];

    for ( int ix = 1; ix < _size; ++ix )
          if ( max_val < _ia[ix] ) 
	       max_val = _ia[ix];

    return max_val;
}

template <class elemType>
    int Array<elemType>::find( const elemType &val )
{ 
    for ( int ix = 0; ix < _size; ++ix )
          if ( val == _ia[ix] ) 
	       return ix;

    return -1;
}

template <class elemType>
    void Array<elemType>::swap( int i, int j )
{
     elemType tmp = _ia[i];
     _ia[i] = _ia[j];
     _ia[j] = tmp;
}

template <class elemType>
    void Array<elemType>::sort( int low, int high )
{ 
    if ( low >= high ) return;
    int lo = low;
    int hi = high + 1;
    elemType elem = _ia[low];

    for ( ;; ) {
         while ( _ia[++lo] < elem ) ;
         while ( _ia[--hi] > elem ) ;
         if ( lo < hi )
              swap( lo,hi );
         else break;
    }  

    swap( low, hi );
    sort( low, hi-1 );
    sort( hi+1, high );
}

#endif
