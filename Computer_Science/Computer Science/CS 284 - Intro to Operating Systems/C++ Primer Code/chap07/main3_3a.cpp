// Section 7.3.3
// $ CC putval1.cpp main3_3a.cpp

/*
  ( 1 )< 23 >
  ( 2 )< 15, 5 >
*/

// defined in putval1.cpp 
void putValues( int[], int size );

int main() {
	int i = 23, j[ 2 ] = { 15, 5 };
	putValues( &i, 1 );
	putValues( j, 2 );
	return 0;
}
