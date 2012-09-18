/****
 *  Mike's sample solution for lab 19
 * Define a myInt class & member functions to do
 *
 * a. Is it a multiple of 7, 11, or 13?
 * b. Is the number odd or even?
 * c. What is the square root of the number?
 *
 * test your methods, using the input values 104, 3773, 13, 121, 77, and 3075.
 *
 ****/

#include <iostream>
#include <cassert>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

//Class definition
class myInt {
public:
    //Constructors
    myInt();
    myInt(int outInput);

    //Member Functions
    bool multiple7();
    bool multiple11();
    bool multiple13();
    bool multiples();
    bool even();
    bool odd();
    double srt();
    void setInt(int newInt);
    void print();

private:
    int localInt;
};

int main() {
    myInt thisInt;

    int ourInputs[6] = {104, 3773, 13, 121, 77, 3075};

    for (int x = 0; x < 6; ++x) {
        thisInt.setInt(ourInputs[x]);
        if (thisInt.multiples()) {
            if (thisInt.multiple7())
                cout << thisInt.print() << " is a multiple of 7" << endl;
            if (thisInt.multiple11())
                cout << thisInt.print() << " is a multiple of 11" << endl;
            if (thisInt.multiple13())
                cout << thisInt.print() << " is a multiple of 13" << endl;
        }
        if (thisInt.even())
            cout << thisInt.print() << " is even" << endl;
        else
            cout << thisInt.print() << " is even" << endl;

        cout << "The square root of " << thisInt.print() << " = " << thisInt.srt();
    }

    return 0;
}

//Constructors
myInt::myInt() { //default constructor sets the int to 0
    localInt = 0;
}

myInt::myInt(int outInput) {
    localInt = outInput;
}

//Member Functions
bool myInt::multiple7() {
    return (localInt % 7 == 0);
}

bool myInt::multiple11() {
    return (localInt % 11 == 0);
}

bool myInt::multiple13() {
    return (localInt % 13 == 0);
}

bool myInt::multiples() {
    return (multiple7() || multiple11() || multiple13());
}

bool myInt::even() {
    return (localInt % 2 == 0);
}

bool myInt::odd() {
    return (! even()); //the opposite of even
}

double myInt::srt() {
    return sqrt(static_cast <int> (localInt));
}

void myInt::setInt(int newInt) {
    localInt = newInt;
    return;
}

void myInt::print() {
    cout << localInt;
    return;
}