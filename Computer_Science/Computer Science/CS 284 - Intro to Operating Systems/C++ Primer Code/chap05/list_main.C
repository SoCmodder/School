#include <iostream.h>
#include "list.h"

int main()
{
/*
 * Ok: after insert_front() and insert_end()
 * 
 * ( 20 )( 9 8 7 6 5 4 3 2 1 0 0 1 2 3 4 5 6 7 8 9 )
 * 
 * Searching for the value 8: found it? yes!
 * 
 * Inserting element 1024 following the value 8
 * 
 * ( 21 )( 9 8 1024 7 6 5 4 3 2 1 0 0 1 2 3 4 5 6 7 8 9 )
 * 
 * Removed 2 of the value 8
 * 
 * ( 19 )( 9 1024 7 6 5 4 3 2 1 0 0 1 2 3 4 5 6 7 9 )
 * 
 * Removed front element
 * 
 * ( 18 )( 1024 7 6 5 4 3 2 1 0 0 1 2 3 4 5 6 7 9 )
 * 
 * Removed all elements
 * 
 * ( 0 )( )
 ***/
    list< int >  mylist;

    for ( int ix = 0; ix < 10; ++ix ) {
	  mylist.insert_front( ix );
          mylist.insert_end( ix );
    }

    cout << "Ok: after insert_front() and insert_end()\n"; 
    mylist.display();

    list_item<int> *it = mylist.find( 8 );
    cout << "\n" 
	 << "Searching for the value 8: found it?"
	 << ( it ? " yes!\n" : " no!\n" );

    mylist.insert( it, 1024 );
    cout << "\n" 
	 << "Inserting element 1024 following the value 8\n";
    mylist.display();

    int elem_cnt = mylist.remove( 8 );
    cout << "\n" 
	 << "Removed " << elem_cnt << " of the value 8\n";

    mylist.display();

    cout << "\n" << "Removed front element\n"; 
    mylist.remove_front(); mylist.display();

    cout << "\n" << "Removed all elements\n"; 
    mylist.remove_all(); mylist.display();
}
