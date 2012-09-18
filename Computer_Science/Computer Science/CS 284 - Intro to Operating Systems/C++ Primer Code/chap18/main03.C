#include "Array_S.C"
#include "try_array.C"
#include <string>

main()
{
    static int ia[ 10 ] = { 12,7,14,9,128,17,6,3,27,5 };
    static string sa[ 7 ] = {
  	"Eeyore", "Pooh", "Tigger",
  	"Piglet", "Owl", "Gopher", "Heffalump"
    };

    Array_Sort<int> iA( ia,10 );
    Array_Sort<string> SA( sa,7 );

    cout << "class template instantiation Array_Sort<int>" << endl;
    try_array( iA );

    cout << "class template instantiation Array_Sort<string>" << endl;
    try_array( SA );

    return 0;
}

