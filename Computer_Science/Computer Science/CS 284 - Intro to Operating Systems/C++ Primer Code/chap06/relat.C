#include <vector>
#include <iostream.h>

void print_elements( int elem ) { cout << elem << " "; }
void (*pfi)( int ) = print_elements;

/*
 * enerates:
ivec1: 1 3 5 7 9 12 
ivec2: 0 1 1 2 3 5 8 13 
ivec3: 1 3 9 
ivec4: 1 3 5 7 
ivec5: 2 4 

ivec1 < ivec2 false
ivec2 < ivec1 true

ivec1 < ivec3 true
ivec1 < ivec4 false
ivec1 < ivec5 true

ivec1 == ivec1 true
ivec1 == ivec4 false
ivec1 != ivec4 true

ivec1 > ivec2 true
ivec3 > ivec1 true
ivec5 > ivec2 true
*/

int main()
{
    void (*pfi)( int ) = print_elements;

    int ia1[6] = { 1,3,5,7,9,12 };
    int ia2[8] = { 0,1,1,2,3,5,8,13 };
    int ia3[3] = { 1,3,9 };
    int ia4[4] = { 1,3,5,7 };
    int ia5[2] = { 2,4 };

    vector<int> ivec1( ia1, ia1+6 );
    vector<int> ivec2( ia2, ia2+8 );
    vector<int> ivec3( ia3, ia3+3 );
    vector<int> ivec4( ia4, ia4+4 );
    vector<int> ivec5( ia5, ia5+2 );

    cout << "ivec1: "; for_each( ivec1.begin(), ivec1.end(), pfi ); cout << "\n";
    cout << "ivec2: "; for_each( ivec2.begin(), ivec2.end(), pfi ); cout << "\n";
    cout << "ivec3: "; for_each( ivec3.begin(), ivec3.end(), pfi ); cout << "\n";
    cout << "ivec4: "; for_each( ivec4.begin(), ivec4.end(), pfi ); cout << "\n";
    cout << "ivec5: "; for_each( ivec5.begin(), ivec5.end(), pfi ); cout << "\n\n";

    cout << "ivec1 < ivec2 " << (ivec1 < ivec2 ? "true" : "false") << "\n";
    cout << "ivec2 < ivec1 " << (ivec2 < ivec1 ? "true" : "false") << "\n\n";

    cout << "ivec1 < ivec3 " << (ivec1 < ivec3 ? "true" : "false") << "\n";
    cout << "ivec1 < ivec4 " << (ivec1 < ivec4 ? "true" : "false") << "\n";
    cout << "ivec1 < ivec5 " << (ivec1 < ivec5 ? "true" : "false") << "\n\n";

    cout << "ivec1 == ivec1 " << (ivec1 == ivec1 ? "true" : "false") << "\n";
    cout << "ivec1 == ivec4 " << (ivec1 == ivec4 ? "true" : "false") << "\n";
    cout << "ivec1 != ivec4 " << (ivec1 != ivec4 ? "true" : "false") << "\n\n";

    cout << "ivec1 > ivec2 "  << (ivec1 > ivec2  ? "true" : "false") << "\n";
    cout << "ivec3 > ivec1 "  << (ivec3 > ivec1  ? "true" : "false") << "\n";
    cout << "ivec5 > ivec2 "  << (ivec5 > ivec2  ? "true" : "false") << "\n";
}    
