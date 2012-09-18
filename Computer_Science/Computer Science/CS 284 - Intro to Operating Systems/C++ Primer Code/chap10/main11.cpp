// Section 10.11
// $ CC main11.C

/*
  sort array of doubles (size == 10)
  < 1.7 5.7 11.7 15.7 19.7 26.7 37.7 48.7 59.7 61.7 >
  sort array of ints (size == 16)
  < 61 87 154 170 275 426 503 509 512 612 653 677 703 765 897 908 >
  sort array of strings (size == 11)
  < a falling heavy left police snow station the they was when >
*/

#include <string>
using std::string;

#include "Array.h"
#include "Array.cpp"
#include "Algo.cpp"

double da[10] = {
        26.7, 5.7, 37.7, 1.7, 61.7, 11.7, 59.7,
        15.7, 48.7, 19.7 };

int ia[16] = {
        503, 87, 512, 61, 908, 170, 897, 275, 653,
        426, 154, 509, 612, 677, 765, 703 };

string sa[11] = {
        "a", "heavy", "snow", "was", "falling", "when",
        "they", "left", "the", "police", "station" };

int main() {

        // call the constructor to initialize arrd
        Array<double> arrd( da, sizeof(da)/sizeof(da[0]) );

        // call the constructor to initialize arri
        Array<int> arri( ia, sizeof(ia)/sizeof(ia[0]) );

        // call the constructor to initialize arrs
        Array<string> arrs( sa, sizeof(sa)/sizeof(sa[0]) );

        cout << "sort array of doubles (size == "
             << arrd.size() << ")" << endl;
        sort(arrd, 0, arrd.size()-1 );
        display(arrd);

        cout << "sort array of ints (size == "
             << arri.size() << ")" << endl;
        sort(arri, 0, arri.size()-1 );
        display(arri);

        cout << "sort array of strings (size == "
             << arrs.size() << ")" << endl;
        sort(arrs, 0, arrs.size()-1 );
        display(arrs);

        return 0;
}
