#include "Array_RC.C"
#include "try_array.C"

main()
{
    static int ia[10] = { 12,7,14,9,128,17,6,3,27,5 };

    Array_RC<int> iA( ia,10 );

    cout << "class template instantiation Array_RC<int>"
 	 << endl;

    try_array( iA );

    return 0;
}

