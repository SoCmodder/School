// Section 16.7
// $ CC main7.cpp

/*
  < 0 3 6 9  >
  < 2 4 6 8 10  >
*/

#include "Queue.h"
#include "Queue.cpp"
using std::cout;

#include <vector>
using std::vector;

int main()
{
        // instantiation of Queue<int>
        Queue<int> qi;

        // instantiation of Queue<int>::assign( int *, int * )
        int ai[4] = { 0, 3, 6, 9 };
        qi.assign( ad, ad + 4 );
	cout << qi << '\n';

        // instantiation of Queue<int>::assign( vector<int>::iterator,
        //                                      vector<int>::iterator)
        int ai2[5] = { 2, 4, 6, 8, 10 };
        vector<int> vi( ai2, ai2 + 5 );
        qi.assign( vi.begin(), vi.end() );
	cout << qi << '\n';
}

