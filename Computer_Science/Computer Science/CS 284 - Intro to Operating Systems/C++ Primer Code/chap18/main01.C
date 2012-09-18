#include "Array.C"
#include "try_array.C"
#include <string>

int main()
{
    static int ia[] = { 12,7,14,9,128,17,6,3,27,5 };
    static double da[] = {12.3,7.9,14.6,9.8,128.0 };
    static string sa[] = { 
	"Eeyore", "Pooh", "Tigger",
 	"Piglet", "Owl", "Gopher", "Heffalump" 
    };

    Array<int>    iA( ia, sizeof(ia)/sizeof(int) );
    Array<double> dA( da, sizeof(da)/sizeof(double) );
    Array<string> sA( sa, sizeof(sa)/sizeof(string) );

    cout << "template Array<int> class\n" << endl;
    try_array(iA);

    cout << "template Array<double> class\n" << endl;
    try_array(dA);

    cout << "template Array<string> class\n" << endl;
    try_array(sA);
}
