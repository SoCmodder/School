#include <iostream.h>

int find_first(char Phrase[], char Word[]);

int main()
{
	char inPhrase[30], inWord[30];
	int iAnswer;
	cout << "Enter Phrase\n";
	cin.getline(inPhrase, 30);
	cout << "Enter Word\n";
	cin.getline(inWord, 30);
	iAnswer = find_first(inPhrase, inWord);
	if (iAnswer == 0)
		cout << "Word is not in Phrase\n";
	else 
		cout << "Word is in position " << iAnswer << endl;

	return 0;
}

int find_first(char Phrase[], char Word[])
{
	int phr_cnt(0), wrd_cnt(0), iPosition(0);
	while(Phrase[phr_cnt] != '\0')
	{
		if(Word[wrd_cnt] == Phrase[phr_cnt])
		{
			iPosition = wrd_cnt;
			wrd_cnt++;
			phr_cnt++;
			if (Word[wrd_cnt] == '\0')
				return (phr_cnt - iPosition);
		}
		else
		{
			phr_cnt++;
		}
	}
	return (iPosition);
}
