#include <iostream>
using std::cout;
using std::endl;

const int max = 65000;
const int lineLength = 12;

void fibonacci( int max )
{
        if ( max < 2 ) return;
                cout << "0 1 ";

        int v1 = 0, v2 = 1, cur;
        for ( int ix = 3; ix <= max; ++ix ) {
                cur = v1 + v2;
                if ( cur > ::max ) break;
                cout << cur << " ";
                v1 = v2;
                v2 = cur;
                if (ix % lineLength == 0) cout << endl;
        }
}
