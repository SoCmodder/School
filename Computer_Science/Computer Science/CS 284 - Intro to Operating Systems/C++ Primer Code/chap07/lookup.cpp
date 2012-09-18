#include <vector>
using std::vector;

// the reference parameter 'occurs' may
// contain a second return value

vector<int>::const_iterator look_up(
        const vector<int> &vec,
        int value,    // is value in the vector?
        int &occurs ) // how many times?
{
        // res_iter initialized to one-past the last element
        vector<int>::const_iterator res_iter = vec.end();
        occurs = 0;

        for ( vector<int>::const_iterator iter = vec.begin();
              iter != vec.end();
              ++iter )
                if ( *iter == value )
                {
                        if ( res_iter == vec.end() )
                                res_iter = iter;
                        ++occurs;
                }

        return res_iter;
}
