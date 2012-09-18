// #include <iostream>
#include <iostream.h>
#include <ctype.h>

/*****
 *****
 ineluctable modality of the visible

 Number of vowel a:      2
 Number of vowel e:      4
 Number of vowel i:      4
 Number of vowel o:      2
 Number of vowel u:      1
 Number of consonants:   18
 *****
 *****/

int main()
{
	char ch;
	int aCnt=0, eCnt=0, iCnt=0, oCnt=0, uCnt=0;
 	int consonantCnt = 0;

	while ( cin >> ch )
		switch ( ch ) 
		{
			case 'a': case 'A': ++aCnt; break;
			case 'e': case 'E': ++eCnt; break;
			case 'i': case 'I': ++iCnt; break;
			case 'o': case 'O': ++oCnt; break;
			case 'u': case 'U': ++uCnt; break;
    			default:
				if ( isalpha( ch ))
 					++consonantCnt;
				break;
		}

	cout << "Number of vowel a: \t" << aCnt << '\n'
		<< "Number of vowel e: \t" << eCnt << '\n'
		<< "Number of vowel i: \t" << iCnt << '\n'
		<< "Number of vowel o: \t" << oCnt << '\n'
		<< "Number of vowel u: \t" << uCnt << '\n'
		<< "Number of consonants: \t" << consonantCnt << '\n';
}
