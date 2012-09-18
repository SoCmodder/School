#include <algorithm>
#include <string>
#include <vector>
#include <iostream.h>

/* generates when fed this program 
( 
  stanl@john:d.galgs 394 : xsh32 istream_iter.c
  stanl@john:d.galgs 395 : cat istream_iter.c | a.out > out
)

------------------------------------

!= " "\n" #include % ( ) *iter ++iter
++line_cnt , 1 9 : ; << <algorithm> <iostream.h>
<string> <vector> = > >::difference_type >::iterator ? allocator back_inserter(
cin copy( cout diff_type eos for in in( int
istream_iterator< it iter line_cnt main() sort( string text text.begin()
text.end() text.erase( typedef unique( vector< { }
*/

int main() 
{
          typedef vector< string , allocator >::difference_type diff_type ;
          istream_iterator< string , diff_type > in( cin ) , eos ;
	  vector< string , allocator > text ;

	  copy( in , eos , back_inserter( text ) ) ;

	  sort( text.begin() , text.end() ) ;

	  vector< string , allocator >::iterator it ;
          it = unique( text.begin() , text.end() ) ;

	  text.erase( it , text.end() ) ;

	  int line_cnt = 1 ;
	  for ( vector< string , allocator >::iterator iter = text.begin() ;
	        iter != text.end() ; ++iter , ++line_cnt )
		     cout << *iter 
                          << ( line_cnt % 9 ? " " : "\n" ) ;
}

