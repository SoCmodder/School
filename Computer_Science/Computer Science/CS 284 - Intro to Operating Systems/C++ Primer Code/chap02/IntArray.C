#include <assert.h>
#include "IntArray.h"

const int IntArray::DefaultArraySize = 12;

void 
IntArray::
init( const int *array, int sz )
{
    if ( ! array ) { _size = 0; _ia = 0; }
    if ( sz < 1 ) sz = 1;

    _size = sz;
    _ia = new int[ _size ];

    for ( int ix = 0; ix < _size; ++ix )
	  _ia[ ix ] = array[ ix ];
}

IntArray&
IntArray::
operator=( const IntArray &iA )
{
    if ( this == &iA )
         return *this;

    delete[] _ia;
    init( iA._ia, iA._size );

    return *this;
}

ostream&
operator<<( ostream &os, IntArray &ar )
{
    return ar.print( os );
}

ostream& 
IntArray::
print( ostream &os ) const
{
    const int lineLength = 12;
    os << "( " << _size << " )< ";

    for ( int ix = 0; ix < _size; ++ix )
    {
          if ( ix % lineLength == 0 && ix )
               os << "\n\t";

          os << _ia[ ix ];
          if ( ix % lineLength != lineLength-1 && ix != _size-1 )
               os << ", ";
    }

    os << " >\n";
    return os;
}

void 
IntArray::
grow()
{ 
    int *oldia = _ia;
    int oldSize = _size;

    _size = oldSize + oldSize/2 + 1;
    _ia   = new int[_size];

    int ix;
    for ( ix = 0; ix < oldSize; ++ix)
          _ia[ix] = oldia[ix];

    for ( ; ix < _size; ++ix )
	  _ia[ix] = 0;

    delete[] oldia;
}

int 
IntArray::
min() const
{
    assert( _ia != 0 );
    int min_val = _ia[0];

    for ( int ix = 1; ix < _size; ++ix )
          if ( _ia[ix] < min_val )
               min_val = _ia[ix];

    return min_val;
}

int 
IntArray::
max() const
{
    assert( _ia != 0 );
    int max_val = _ia[0];

    for ( int ix = 1; ix < _size; ++ix )
          if ( max_val < _ia[ix] ) 
	       max_val = _ia[ix];

    return max_val;
}

int 
IntArray::
find( int val ) const
{ 
    for ( int ix = 0; ix < _size; ++ix )
          if ( val == _ia[ix] ) 
	       return ix;

    return -1;
}

void 
IntArray::
swap( int i, int j )
{
     int tmp = _ia[i];
     _ia[i] = _ia[j];
     _ia[j] = tmp;
}

void 
IntArray::
sort( int low, int high )
{ 
    if ( low >= high ) return;
    int lo = low;
    int hi = high + 1;
    int elem = _ia[low];

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
