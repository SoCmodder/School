// #include <iostream>

#include <algorithm>
#include <string>
#include <vector>
#include <iostream.h>

/**
 **

  io20_2.03 < alice_emma

  "Daddy, "I A Alice Daddy Daddy, Emma Her Shyly,
  a alive, almost asks, at beautiful bird bird, blows
  but creature," fiery flight. flowing hair, hair. has he
  her her, him him, in is it like long
  looks magical mean, more. no red same says she
  shush, such tell tells the there there?" through time
  to untamed. wanting when wind 

 **/

int main()
{
 	istream_iterator< string > in( cin ), eos ;
 	vector< string > text ;

	// copy the values read from standard input into text
 	copy( in , eos , back_inserter( text ) ) ;
 	sort( text.begin() , text.end() ) ;

 	// remove all duplicate values
 	vector< string >::iterator it;
 	it = unique( text.begin() , text.end() ) ;
 	text.erase( it , text.end() ) ;

 	// display the resulting vector
 	int line_cnt = 1 ;
 	for ( vector< string >::iterator iter = text.begin() ;
        	      iter != text.end() ; ++iter , ++line_cnt )
     	      cout << *iter
                   << ( line_cnt % 9 ? " " : "\n" ) ;

 	cout << endl;
}
