// Section 16.3
// $ CC main3.cpp

/*

 !! queue executed ok

*/

#include "Queue.h"
#include "Queue.cpp"
using std::cout;
using std::endl;

int main()
{
        // the class Queue<int> is instantiated
        // new expression requires that Queue<int> be defined
        Queue<int> *p_qi = new Queue<int>;

        int ival;
        for ( ival = 0; ival < 10; ++ival )
                // the member function add() is instantiated
                p_qi->add( ival );

        int err_cnt = 0;
        for ( ival = 0; ival < 10; ++ival ) {
                // the member function remove() is instantiated
                int qval = p_qi->remove();

                if ( ival != qval ) err_cnt++;
        }

        if ( !err_cnt )
                cout << "!! queue executed ok\n";
        else cerr << "?? queue errors: " << err_cnt << endl;
        return 0;
}
