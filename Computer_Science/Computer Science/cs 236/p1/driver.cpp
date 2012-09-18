/**************************************
 *  File Name  :  driver.cpp
 *  Function   :  test driver for program # 1
 *  Programmer :  Franck Xia, CS Dept. UMR
 *  Creation   :  Jan. 26, 2002
 **************************************/

 #include <iostream.h>
 #include <fstream.h>
 #include "cppmatrix.h"

 int main()
 {
    int row, col;

    ifstream in_file("input_file.dat");

//  read from the file data for the first matrix

    in_file >> row >> col;
    cppmatrix a(row, col);
    in_file >> a;

//  read from the file data for the second matrix

    in_file >> row >> col;
    cppmatrix b(row, col);
    in_file >> b;

    cout << "The first operand a (of + or -): \n";
    cout << a;

    cout << "The second operand b: \n";
    cout << b;

    cout << "Here is the result of a + b: \n";
    cout << a + b;

    cout << "and the result of a - b: \n";
    cout << a - b;

//  reading data for the first multiplication

    in_file >> row >> col;
    cppmatrix c(row, col);
    in_file >> c;

    in_file >> row >> col;
    cppmatrix d(row, col);
    in_file >> d;

    cout << "The first operand c (of *): \n";
    cout << c;

    cout << "The second operand d: \n";
    cout << d;

    cout << "Here is the result of c * d: \n";
    cout << c * d;

//  reading data for the second multiplication

    in_file >> row >> col;
    cppmatrix e(row, col);
    in_file >> e;

    in_file >> row >> col;
    cppmatrix f(row, col);
    in_file >> f;

    cout << "The first operand e (of *): \n";
    cout << e;

    cout << "The second operand f: \n";
    cout << f;

    cout << "Here is the result of e * f: \n";
    cout << e * f;

    return 0;
 }
