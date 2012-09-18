// #include <iostream>
#include <iostream.h>

/*****
 *****
 aeiou

 Number of vowel a:      1
 Number of vowel e:      2
 Number of vowel i:      3
 Number of vowel o:      4
 Number of vowel u:      5
 *****
 *****/

int main()
{
	char ch;
	int aCnt=0, eCnt=0, iCnt=0, oCnt=0, uCnt=0;

	// incorrect version: missing break
	while ( cin >> ch )
		// warning: deliberately incorrect!
		// each case following matching case is
		//      also executed
		switch ( ch ) 
		{
			case 'a':
				++aCnt;

			case 'e':
				++eCnt;

			case 'i':
				++iCnt;

			case 'o':
				++oCnt;

			case 'u':
				++uCnt;
		}

	cout << "Number of vowel a: \t" << aCnt << '\n'
		<< "Number of vowel e: \t" << eCnt << '\n'
		<< "Number of vowel i: \t" << iCnt << '\n'
		<< "Number of vowel o: \t" << oCnt << '\n'
		<< "Number of vowel u: \t" << uCnt << '\n';
}

