// #include <iostream>
#include <iostream.h>
#include <vector>

/**
 ** Minimum value: 1 occurs: 5 times.
 **/

int min( const vector< int > &ivec, int &occurs )
{
        int minVal = ivec[ 0 ];
        occurs = 1;
        int size = ivec.size();
        for ( int ix = 1; ix < size; ++ix )
        {
                if ( minVal == ivec[ ix ] )
                        ++occurs;
                else
                if ( minVal > ivec[ ix ] )
 		{
                        minVal = ivec[ ix ];
                        occurs = 1;
                }
        }
        return minVal;
}

int main()
{
        int ia[14] = { 9,1,7,1,4,8,1,3,7,2,6,1,5,1 };
        vector<int> ivec( ia, ia+14 );

        int occurs = 0;
        int minVal = min( ivec, occurs );

        cout << "Minimum value: " << minVal
             << " occurs: " << occurs << " times.\n";

        return 0;
}

