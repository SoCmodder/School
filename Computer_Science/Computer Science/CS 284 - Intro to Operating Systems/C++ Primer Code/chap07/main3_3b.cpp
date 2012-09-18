// Section 7.3.3
// $ CC putval2.cpp main3_3a.cpp

// defined in putval2.cpp
// parameter is a reference to an array of 10 ints
void putValues( int (&arr)[10] );

int main() {
	int i = 23, j[ 2 ] = { 15, 5 };
	putValues( i ); // error: argument is not an array of 10 ints
	putValues( j ); // error: argument is not an array of 10 ints
	return 0;
}
