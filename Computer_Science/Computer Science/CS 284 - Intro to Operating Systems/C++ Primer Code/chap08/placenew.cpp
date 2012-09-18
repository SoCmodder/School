// Section 8.4.5
// $ CC placenew.cpp

/*
  new expression worked!
*/

#include <iostream>
using std::cout;
using std::endl;

#include <new.h>

const int chunk = 16;

class Foo {
public:
        int val()  { return _val; }
        Foo() { _val = 0; }
private:
        int _val;
};

// preallocate the memory, but no Foo objects
char *buf = new char[ sizeof(Foo) * chunk ];

int main() {
        // create a Foo object in buf
        Foo *pb = new (buf) Foo;

        // check that an object was placed in buf
        if ( pb->val() == 0 )
                cout << "new expression worked!" << endl;

        // cannot use pb here
        delete[] buf;

        return 0;
}
