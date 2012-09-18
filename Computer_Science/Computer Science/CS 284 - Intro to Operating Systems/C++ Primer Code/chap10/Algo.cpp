#ifndef ALGO_C
#define ALGO_C

template <class Type>
        Type min( Type a, Type b ) {
                return a < b ? a : b;
}

template <class elemType>
        void swap( Array<elemType> &array, int i, int j )
{
        elemType tmp = array[ i ];
        array[ i ] = array[ j ];
        array[ j ] = tmp;
}

template <class elemType>
        void sort( Array<elemType> &array, int low, int high ) {
        if ( low < high ) {
                int lo = low;
                int hi = high + 1;
                elemType elem = array[lo];

                for (;;) {
                        while ( min( array[++lo], elem ) != elem && lo < high ) ;
                        while ( min( array[--hi], elem ) == elem && hi > low ) ;

                        if (lo < hi)
                                swap( array, lo, hi );
                        else break;
                }

                swap( array, low, hi );
                sort( array, low, hi-1 );
                sort( array, hi+1, high );
        }
}

template <class elemType>
        void display( Array<elemType> &array )
{ // display format: < 0 1 2 3 4 5 >

        cout << "< ";
        for ( int ix = 0; ix < array.size(); ++ix )
                cout << array[ix] << " ";
        cout << ">\n";
}

#endif
