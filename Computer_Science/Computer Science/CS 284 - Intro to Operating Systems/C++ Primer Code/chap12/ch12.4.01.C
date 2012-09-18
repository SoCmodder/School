#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
/*
 * input:
 * 23 109 45 89 6 34 12 90 34 23 56 23 8 89 23
 *
 * output:
 * 109 90 89 56 45 34 23 12 8 6
 */
int main()
{
        istream_iterator< int > input( cin );
        istream_iterator< int > end_of_stream;
        vector<int> vec;

        copy ( input, end_of_stream, inserter( vec, vec.begin() ));
        sort( vec.begin(), vec.end(), greater<int>() );

        ostream_iterator< int > output( cout, " " );
        unique_copy( vec.begin(), vec.end(), output );
}
