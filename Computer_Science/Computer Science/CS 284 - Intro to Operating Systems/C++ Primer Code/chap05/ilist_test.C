#include <iostream.h>
#include "ilist.h"

int main()
{

    /* 
     * ----------------------------------------------------
     * test #1: items at end
     * ----------------------------------------------------
     * 
     * ( 6 )( 4 3 2 1 1 1 )
     * 
     * Removed 3 of the value 1
     * 
     * ( 3 )( 4 3 2 )
     * 
     * ----------------------------------------------------
     * test #2: items at front
     * ----------------------------------------------------
     * 
     * ( 3 )( 1 1 1 )
     * 
     * Removed 3 of the value 1
     * 
     * ( 0 )( )
     * 
     * ----------------------------------------------------
     * test #3: no items present
     * ----------------------------------------------------
     * 
     * ( 3 )( 4 2 0 )
     * 
     * Removed 0 of the value 1
     * 
     * ( 3 )( 4 2 0 )
     * 
     * ----------------------------------------------------
     * test #4: items at front and end
     * ----------------------------------------------------
     * 
     * ( 9 )( 1 1 1 4 2 0 1 1 1 )
     * 
     * Removed 6 of the value 1
     * 
     * ( 3 )( 4 2 0 )
     */

    ilist mylist;

     cout << "\n----------------------------------------------------\n"
	  << "test #1: items at end\n"
	  << "----------------------------------------------------\n";

     mylist.insert_front( 1 ); mylist.insert_front( 1 ); mylist.insert_front( 1 );
     mylist.insert_front( 2 ); mylist.insert_front( 3 ); mylist.insert_front( 4 );

     mylist.display();

     int elem_cnt = mylist.remove( 1 );
     cout << "\n" << "Removed " << elem_cnt << " of the value 1\n";
     mylist.display();

     mylist.remove_all();

     cout << "\n----------------------------------------------------\n"
          << "test #2: items at front\n"
	  << "----------------------------------------------------\n";

     mylist.insert_front( 1 ); mylist.insert_front( 1 ); mylist.insert_front( 1 );
     mylist.display();

     elem_cnt = mylist.remove( 1 );
     cout << "\n" << "Removed " << elem_cnt << " of the value 1\n";
     mylist.display();

     mylist.remove_all();

     cout << "\n----------------------------------------------------\n"
          << "test #3: no items present\n"
	  << "----------------------------------------------------\n";

     mylist.insert_front( 0 ); mylist.insert_front( 2 ); mylist.insert_front( 4 );
     mylist.display();

     elem_cnt = mylist.remove( 1 );
     cout << "\n" << "Removed " << elem_cnt << " of the value 1\n";
     mylist.display();

     mylist.remove_all();

     cout << "\n----------------------------------------------------\n"
          << "test #4: items at front and end\n"
	  << "----------------------------------------------------\n";

     mylist.insert_front( 1 ); mylist.insert_front( 1 ); mylist.insert_front( 1 );
     mylist.insert_front( 0 ); mylist.insert_front( 2 ); mylist.insert_front( 4 );
     mylist.insert_front( 1 ); mylist.insert_front( 1 ); mylist.insert_front( 1 );
     mylist.display();

     elem_cnt = mylist.remove( 1 );
     cout << "\n" << "Removed " << elem_cnt << " of the value 1\n";
     mylist.display();
}
