#include "Array_S.h"
#include "Array.C"

template <class elemType>
Array_Sort<elemType>::
Array_Sort( const Array_Sort<elemType> &as )
          : Array<elemType>( as )
{
    if ( as.is_dirty() )
         sort( 0, Array<elemType>::_size-1 );
    clear_bit();
}

/*******************************
// an alternative implementation
template <class elemType>
Array_Sort<elemType>::
Array_Sort( const Array_Sort<elemType> &as )
          : Array<elemType>( as )
{
    dirty_bit = as.dirty_bit;
    check_bit();
}
********************************/

template <class elemType>
void 
Array_Sort<elemType>::
grow()
{
    Array<elemType>::grow();
    sort( 0, Array<elemType>::_size-1 );
    clear_bit();
}

template <class elemType>
int 
Array_Sort<elemType>::
find( const elemType &val )
{
     int low = 0;
     int high = Array<elemType>::_size-1;
     check_bit();
     while ( low <= high ) 
     {
          int mid = ( low + high )/2;

          if ( val == _ia[ mid ])
               return mid;

          if ( val < _ia[ mid ] )
               high = mid-1;
          else low = mid+1;
     }

     return -1;
}

