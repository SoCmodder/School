// #include <iostream>
#include <iostream.h>

/**
 ** generates:

  Alice Emma has long flowing red hair. Her Daddy says
  when the wind blows through her hair, it looks almost alive,
  like a fiery bird in flight. A beautiful fiery bird, he tells her,
  magical but untamed. "Daddy, shush, there is no such creature,"
  she tells him, at the same time wanting him to tell her more.
  Shyly, she asks, "I mean, Daddy, is there?"

  our statistics:
        spaces: 59      new lines: 6    tabs: 0
        periods: 4      commas: 12
 **
 **/

int main() 
{ 
	char ch;
	int  tab_cnt = 0, nl_cnt = 0, space_cnt = 0,
		period_cnt = 0, comma_cnt = 0;

	while (cin.get(ch)) {
		switch( ch ) {
			case ' ':  space_cnt++;  break;
			case '\t': tab_cnt++;    break;
			case '\n': nl_cnt++;     break;
			case '.':  period_cnt++; break;
			case ',':  comma_cnt++;  break;
		}
		cout.put(ch);
	}

	cout << "\nour statistics:\n\t" 
		<< "spaces: "    << space_cnt  << '\t'
		<< "new lines: " << nl_cnt     << '\t'
		<< "tabs: "      << tab_cnt    << "\n\t"
		<< "periods: "   << period_cnt << '\t'
		<< "commas: "    << comma_cnt  << endl;
}

