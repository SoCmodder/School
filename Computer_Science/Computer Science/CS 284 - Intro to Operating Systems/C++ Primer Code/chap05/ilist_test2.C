#include <iostream.h>
#include "ilist.h"

int main()
{

    /*
     *
     * ( 10 )( 9 8 7 6 5 4 3 2 1 0 )
     * 
     * reverse the list
     * 
     * ( 10 )( 0 1 2 3 4 5 6 7 8 9 )
     * 
     * mylist_too:
     * 
     * ( 6 )( 0 1 1 2 3 5 )
     * 
     * mylist after concat with mylist_too:
     * 
     * ( 16 )( 0 1 2 3 4 5 6 7 8 9 0 1 1 2 3 5 )
     */
 
     ilist mylist;

     for ( int ix = 0; ix < 10; ++ix ) 
         { mylist.insert_front( ix ); }

     mylist.display();

     cout << "\n" << "reverse the list\n";
     mylist.reverse(); mylist.display();

     ilist mylist_too;
     mylist_too.insert_end( 0 ); mylist_too.insert_end( 1 ); 
     mylist_too.insert_end( 1 ); mylist_too.insert_end( 2 ); 
     mylist_too.insert_end( 3 ); mylist_too.insert_end( 5 );

     cout << "\n" << "mylist_too:\n";
     mylist_too.display();

     mylist.concat( mylist_too );
     cout << "\n" << "mylist after concat with mylist_too:\n";
     mylist.display();

}
