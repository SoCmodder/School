#include <complex>
#include <iostream.h>

inline complex< double >&
operator+=( complex< double > &c, double dval )
{
    return c += complex< double >( dval );
}

inline complex< double >&
operator++( complex< double > &c )
{
    return c += complex< double >( 1.0 );
}

int main()
{
/*
(0,2)
(2,0)
(1,2)
(2,2)
(4,2)
*/
    complex< double > purei( 0, 2 );
    cout << purei << endl;

    complex< double > real( 2 );
    cout << real << endl;

    // error ... 
    // by default, only += complex object
    // ok; overloaded instance
    purei += 1;
    cout << purei << endl;

    ++purei;
    cout << purei << endl;

    purei += real;
    cout << purei << endl;

}
