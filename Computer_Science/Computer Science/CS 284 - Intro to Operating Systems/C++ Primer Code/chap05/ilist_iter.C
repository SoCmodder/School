#include <iostream.h>
#include "ilist.h"

int main()
{
    ilist mylist;

    for ( int ix = 0; ix < 10; ++ix ) {
	  mylist.insert_front( ix );
          mylist.insert_end( ix );
    }

    cout << "\n" << "Use of init_iter() and next_iter() "
	 << "to iterate across each list item:\n";

    ilist_item *iter;
    for ( iter = mylist.init_iter(); iter; iter = mylist.next_iter() )
	  cout << iter->value() << " ";

    cout << "\n" << "Use of copy constructor\n";

    ilist mylist2( mylist );
    mylist.remove_all();

    for ( iter = mylist2.init_iter(); iter; iter = mylist2.next_iter() )
	  cout << iter->value() << " ";

    cout << "\n" << "Use of copy assignment operator\n";

    mylist = mylist2;

    for ( iter = mylist.init_iter(); iter; iter = mylist.next_iter() )
	  cout << iter->value() << " ";

    cout << "\n";

}


