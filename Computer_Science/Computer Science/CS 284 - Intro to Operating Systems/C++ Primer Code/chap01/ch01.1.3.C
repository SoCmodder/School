// #include <iostream>

#include <iostream.h>
#include <vector>
#include <string>

/**
 **
 CC -n32 -experimental -I $EXTERN/include -DDEBUG ch01.1.3.c $EXTERN/lib32/libstd.so
 a.out < input_file
 Beginning execution of main()
 word read: Shyly,
 word read: she
 word read: asks,
 word read: "I
 word read: mean,
 word read: Daddy,
 word read: is
 word read: there?"
 **
 **/

int main()
{

#ifdef DEBUG
	cout << "Beginning execution of main()\n";
#endif

 	string word;
 	vector< string > text;

 	while ( cin >> word )
 	{
#ifdef DEBUG
  		cout << "word read: " << word << "\n";
#endif

  		text.push_back( word );
 	}

 	// ...
}
