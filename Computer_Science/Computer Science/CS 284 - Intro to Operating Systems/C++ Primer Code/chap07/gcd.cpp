int gcd( int v1, int v2 )
{ 
	// return the greatest common divisor
	while ( v2 )
	{
		int temp = v2;
		v2 = v1 % v2;
		v1 = temp;
	}
	return v1;
}
