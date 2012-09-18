// Section 10.8
// $ CC screen.cpp main8.cpp


#include "screen.h"

int main() {
        Screen *ps = new Screen(8, 8, '%');

        ps->display();

        delete ps;
        return 0;
}
