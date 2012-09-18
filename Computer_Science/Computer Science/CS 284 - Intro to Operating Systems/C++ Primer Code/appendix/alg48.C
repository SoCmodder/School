#include <algorithm>
#include <set>
#include <string>
#include <iostream.h>

/* generates:
set #1 elements:
        Eeyore Piglet Pooh Tigger 

set #2 elements:
        Heffalump Pooh Woozles 

set_union() elements:
        Eeyore Heffalump Piglet Pooh Tigger Woozles 

set_intersection() elements:
        Pooh 

set_difference() elements:
        Eeyore Piglet Tigger 

set_symmetric_difference() elements:
        Eeyore Heffalump Piglet Tigger Woozles 
*/
	
int main()
{
	string str1[] = { "Pooh", "Piglet", "Tigger", "Eeyore" }; 
	string str2[] = { "Pooh", "Heffalump", "Woozles" };
        ostream_iterator< string >  ofile( cout, " " );
		
	set<string,less<string>,allocator> set1( str1, str1+4 );
	set<string,less<string>,allocator> set2( str2, str2+3 );

        cout << "set #1 elements:\n\t";
        copy( set1.begin(), set1.end(), ofile ); cout << "\n\n";

        cout << "set #2 elements:\n\t";
        copy( set2.begin(), set2.end(), ofile ); cout << "\n\n";

	set<string,less<string>,allocator> res;
	set_union( set1.begin(), set1.end(),
		   set2.begin(), set2.end(), 
		   inserter( res, res.begin() ));

        cout << "set_union() elements:\n\t";
        copy( res.begin(), res.end(), ofile ); cout << "\n\n";

	res.clear();
	set_intersection( set1.begin(), set1.end(),
                          set2.begin(), set2.end(),
                          inserter( res, res.begin() ));

        cout << "set_intersection() elements:\n\t";
        copy( res.begin(), res.end(), ofile ); cout << "\n\n";

        res.clear();
        set_difference( set1.begin(), set1.end(),
                        set2.begin(), set2.end(),
                        inserter( res, res.begin() ));

        cout << "set_difference() elements:\n\t";
        copy( res.begin(), res.end(), ofile ); cout << "\n\n";

        res.clear();
        set_symmetric_difference( set1.begin(), set1.end(),
                                  set2.begin(), set2.end(),
                                  inserter( res, res.begin() ));

        cout << "set_symmetric_difference() elements:\n\t";
        copy( res.begin(), res.end(), ofile ); cout << "\n\n";
}
