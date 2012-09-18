//Sample Solution for Week 13
// Lab 17 -- Function Overloading
//
// Original code found online (modified slightly)

#include <iostream>
//#include <iomanip>
using std::cout;
using std::endl;
using std::ios;

//Function Declarations
////////////////////////////////////////////////////////////////
// FOR ALL FUNCTIONS:
//Pre:  none
//Post: the second variable is updated with the converted value
//      equivalent to the first input value
void ConvertFToC(double f, double &c);
void ConvertFToC(float f, float &c);
void ConvertFToC(int f, int &c);
void ConvertCToF(double c, double &f);
void ConvertCToF(float c, float &f);
void ConvertCToF(int c, int &f);
////////////////////////////////////////////////////////////////

int main() {

cout.precision (3);
cout.setf(ios::fixed);
cout.setf(ios::showpoint);

    //declares all types of °F & °C values & sets up °F for °C conversions
    float  cfloat,  ffloat = 32.0;
    double cdouble, fdouble = 75.0;
    int    cint,    fint = 75;

    ConvertFToC(fdouble, cdouble);
    cout << fdouble << "°F = " << cdouble << "°C" << endl;

    ConvertFToC(ffloat, cfloat);
    cout << ffloat << "°F = " << cfloat << "°C" << endl;

    ConvertFToC(fint, cint);
    cout << fint << "°F = " << cint << "°C" << endl << endl;

    //sets up °C values for converting to °F
    cdouble = 11.0;
    cfloat = -40.0;
    cint = 11;

    ConvertCToF(cdouble, fdouble);
    cout << cdouble << "°C = " << fdouble << "°F" << endl;

    ConvertCToF(cfloat, ffloat);
    cout << cfloat << "°C = " << ffloat << "°F" << endl;

    ConvertCToF(cint, fint);
    cout << cint << "°C = " << fint << "°F" << endl << endl;

    return 0;
}


void ConvertFToC(double f, double &c) {
    c = (f - 32.0) * 5.0 / 9.0;
    return;
}

void ConvertFToC(float f, float &c) {
    c = (f - 32.0) * 5.0 / 9.0;
    return;
}

void ConvertFToC(int f, int &c) {
    c = static_cast<int>((f - 32.0) * 5.0 / 9.0);
    return;
}

void ConvertCToF(double c, double &f) {
    f = (9.0 / 5.0) * c + 32.0;
    return;
}

void ConvertCToF(float c, float &f) {
    f = (9.0 / 5.0) * c + 32.0;
    return;
}

void ConvertCToF(int c, int &f) {
    f = static_cast<int>((9.0 / 5.0) * c + 32.0);
    return;
}
