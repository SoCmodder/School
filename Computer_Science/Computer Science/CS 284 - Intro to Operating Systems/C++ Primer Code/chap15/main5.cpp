// Section 15.5
// $ CC main5.cpp 

#include <vector>
#include <algorithm>
#include <iostream>

class absInt {
public:
        int operator()( int val ) {
                int result = val < 0 ? -val : val;
                return result;
        }
};

int main() {
	using std::vector;
	using std::transform;
	using std::cout;

        int ia[] = { -0, 1, -1, -2, 3, 5, -5, 8 };
        vector< int > ivec( ia, ia+8 );

        // set each element of ivec to its absolute value
        transform( ivec.begin(), ivec.end(), ivec.begin(), absInt() );

        for ( int ix = 0; ix < ivec.size(); ++ix )
            cout << ivec[ix] << " ";
        cout << "\n";

	return 0;
}

