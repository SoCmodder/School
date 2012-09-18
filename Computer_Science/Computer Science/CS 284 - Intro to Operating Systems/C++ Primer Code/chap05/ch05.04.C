// #include <iostream>
#include <iostream.h>

/*****
 *****
 aeiou
 Number of vowel a:      1
 Number of vowel e:      1
 Number of vowel i:      1
 Number of vowel o:      1
 Number of vowel u:      1
 *****
 *****/

int main()
{
	char ch;
	int aCnt=0, eCnt=0, iCnt=0, oCnt=0, uCnt=0;

	// corrected version: includes break
	while ( cin >> ch )
		switch ( ch ) 
		{
			case 'a':
				++aCnt;
				break;
			case 'e':
				++eCnt;
				break;
			case 'i':
				++iCnt;
				break;
			case 'o':
				++oCnt;
				break;
			case 'u':
				++uCnt;
				break;
		}

	cout << "Number of vowel a: \t" << aCnt << '\n'
		<< "Number of vowel e: \t" << eCnt << '\n'
		<< "Number of vowel i: \t" << iCnt << '\n'
		<< "Number of vowel o: \t" << oCnt << '\n'
		<< "Number of vowel u: \t" << uCnt << '\n';
}
