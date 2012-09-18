// Section 16.13
// $ CC main13.cpp

/*
  template Array<int> class

  try_array: initial array values:
  ( 10 )< 12, 7, 14, 9, 128, 17, 6, 3, 27, 5 >

  try_array: after assignments:
  ( 10 )< 128, 7, 14, 9, 128, 128, 6, 3, 27, 3 >

  try_array: memberwise initialization
  ( 10 )< 128, 7, 14, 9, 128, 128, 6, 3, 27, 3 >

  try_array: after memberwise copy
  ( 10 )< 128, 7, 128, 9, 128, 128, 6, 3, 27, 3 >

  try_array: after grow
  ( 16 )< 128, 7, 128, 9, 128, 128, 6, 3, 27, 3, 0, 0
          0, 0, 0, 0 >

  value to find: 5        index returned: -1
  value found at index: 64
  template Array<double> class

  try_array: initial array values:
  ( 5 )< 12.3, 7.9, 14.6, 9.8, 128 >

  try_array: after assignments:
  ( 5 )< 14.6, 7.9, 14.6, 9.8, 7.9 >

  try_array: memberwise initialization
  ( 5 )< 14.6, 7.9, 14.6, 9.8, 7.9 >

  try_array: after memberwise copy
  ( 5 )< 14.6, 14.6, 14.6, 9.8, 7.9 >

  try_array: after grow
  ( 8 )< 14.6, 14.6, 14.6, 9.8, 7.9, 0, 0, 0 >

  value to find: 128      index returned: -1
  value found at index: 3.35965e-322
  template Array<string> class

  try_array: initial array values:
  ( 7 )< Eeyore, Pooh, Tigger, Piglet, Owl, Gopher, Heffalump >

  try_array: after assignments:
  ( 7 )< Tigger, Pooh, Tigger, Tigger, Owl, Gopher, Eeyore >

  try_array: memberwise initialization
  ( 7 )< Tigger, Pooh, Tigger, Tigger, Owl, Gopher, Eeyore >

  try_array: after memberwise copy
  ( 7 )< Tigger, Tigger, Tigger, Tigger, Owl, Gopher, Eeyore >

  try_array: after grow
  ( 11 )< Tigger, Tigger, Tigger, Tigger, Owl, Gopher, Eeyore, , , ,  >

  value to find: Heffalump        index returned: -1

*/

#include "Array.cpp"
#include "try_array.cpp"

#include <string>
using std::string;

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
