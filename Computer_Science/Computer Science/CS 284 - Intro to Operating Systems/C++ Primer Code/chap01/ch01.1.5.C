// #include <iostream>

#include <iostream.h>
#include <string>

/**
 **
 a.out < input_file
 word read is: Shyly,
 word read is: she
 word read is: asks,
 word read is: "I
 word read is: mean,
 word read is: Daddy,
 word read is: is
 word read is: there?"
 ok: no more words to read: bye!
 **
 **/

int main()
{
 	string word;

 	while ( cin >> word )
       		cout << "word read is: " << word << '\n';

 	cout << "ok: no more words to read: bye!\n";
 	return 0;
}
