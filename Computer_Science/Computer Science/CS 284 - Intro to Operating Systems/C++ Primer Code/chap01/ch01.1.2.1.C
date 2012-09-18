#include <iostream.h>
// #include <iostream>

/**
 **
 the while loop has executed 1 times
 the while loop has executed 2 times
 the while loop has executed 3 times
 the while loop has executed 4 times
 the while loop has executed 5 times
 **
 **/
int main()
{
	int iterations = 0;
	bool continue_loop = true;

	while ( continue_loop != false )
	{
		iterations++;

		cout << "the while loop has executed "
     		     << iterations << " times\n";

		if ( iterations == 5 )
     		     continue_loop = false;
	}

	return 0;
}
