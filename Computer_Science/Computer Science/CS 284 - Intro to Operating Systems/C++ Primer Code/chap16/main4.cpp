// Section 16.4
// $ CC main4.cpp

/*
  <  >
  < 0 1 2 3 4 5 6 7 8 9  >
  <  >
  !! queue executed ok
*/

#include "Queue.h"
#include "Queue.cpp"
using std::cout;
using std::endl;

int main() {
        Queue<int> qi;
        // instantiates both instances:
        //   ostream& operator<<(ostream &os, const Queue<int> &)
        //   ostream& operator<<(ostream &os, const QueueItem<int> &)
        // cout << qi << endl;
	qi.print();

        int ival;
        for ( ival = 0; ival < 10; ++ival )
                qi.add( ival );
        // cout << qi << endl;
	qi.print();

        int err_cnt = 0;
        for ( ival = 0; ival < 10; ++ival ) {
                int qval = qi.remove();
                if ( ival != qval ) err_cnt++;
        }

        // cout << qi << endl;
	qi.print();
        if ( !err_cnt )
                cout << "!! queue executed ok\n";
        else cout << "?? queue errors: " << err_cnt << endl;
        return 0;
}

