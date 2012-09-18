#ifndef ARRAY_C
#define ARRAY_C

#include <cassert>

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

#endif
