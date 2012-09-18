// Section 16.6
// 

/*
  <  >
  < 0 1 2 3 4 5 6 7 8 9  >
  <  >
  !! queue executed ok
*/

// QueueItem is now a nested type of the class template Queue

#include "Queue6.h"
#include "Queue6.cpp"
using std::endl;

int main() {
        Queue<int> qi;
        cout << qi << endl;

        int ival;
        for ( ival = 0; ival < 10; ++ival )
                qi.add( ival );
        cout << qi << endl;

        int err_cnt = 0;
        for ( ival = 0; ival < 10; ++ival ) {
                int qval = qi.remove();
                if ( ival != qval ) err_cnt++;
        }

        cout << qi << endl;
        if ( !err_cnt )
                cout << "!! queue executed ok\n";
        else cout << "?? queue errors: " << err_cnt << endl;
        return 0;
}

