
#include "stdafx.h"
#include <Afx.h>
#include <fstream.h>
#include <iostream.h>
#include <string.h>

int main(void) {
	int pause;
	char aWord[50];
	ifstream Words("c:\\Shakespear.txt",ios::in);
	if(!Words) {
		cerr << "Couldn't open the file" << endl;
		cin >> pause;
		return -1;
	}
	fstream HFile("c:\\ARDK.dat",ios::in | ios::out);
	while(!Words.eof()) {
		int i, word_len;
		unsigned char byte = 0;
		Words >> aWord;
		word_len = strlen(aWord);
		cout << endl;
		for(i = 0; (i<4) && (i<word_len); ++i) {
			byte = byte ^ aWord[i];
			cout << aWord << "(" (int)byte << ")" << '\t';
		}
	}
	cin >> pause;
	return 0;
}
