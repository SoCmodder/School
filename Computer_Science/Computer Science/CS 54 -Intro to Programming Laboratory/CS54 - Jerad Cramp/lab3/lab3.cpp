 /* programmer: robertoMurillo   date: 090705
    file: lab3.cpp     class: cs54 section d
    description: getting used to the Unix environment and also
    playing around with all of the commands. */

  #include <iostream>
  using namespace std;

  int main()
  {

  // program variables
    int i1, i2, intDivide1, intDivide2, c1equation, remainderEq;
    char c1, i1ascii;
    float intDivide3;
    
  // entering integers and output
    cout << "Hello and welcome to CS54's Lab 3 program." << endl;
    cout << endl; // space in between to make program look smoother.
    cout << "Please enter in an Integer: ";
    cin >> i1;
    cout << "Now please enter a second integer, less than the first: ";
    cin >> i2;
    cout << endl; // space in between
    
  // integer equations and output
    intDivide1 = i1 / i2;
    intDivide2 = static_cast<float>( i1 / i2 );
    intDivide3 = i1 / static_cast<float>( i2 );
    
    cout << "Result of Integer divison " << i1 << "/" << i2 << " is "
    << intDivide1 << "." << endl;
    
    cout << "Result of casting the result of Integer division " <<
    i1 << "/" << i2 << " is " << intDivide2 << "." << endl;
    
    cout << "Result of casting the denominator of division " <<
    i1 << "/" << i2 << " is " << intDivide3 << "." << endl;
    cout << endl; // space in between
    
  // now enter in a character
    cout << "Thank you.  Now enter in a character: ";
    cin >> c1;
    cout << endl; // space in between
    
  // char equation for ASCII
    c1equation = static_cast<int>(c1);
    
    cout << "The ASCII code for " << c1 << " is " << c1equation << ".";
    cout << endl; // space in between
    
    cout << "Now, Enter an integer between 48-57, 65-90, 97-122: ";
    cin >> i1;
    cout << endl; // space in between
    
    i1ascii = static_cast<char>(i1);
    
    cout << "The character with ASCII code " << i1 << " is " << i1ascii 
    << ".";
    cout << endl; // space in between
    
    cout << "Now, enter in an integer: ";
    cin >> i1;
    cout << "Enter a second integer, less than the first: ";
    cin >> i2;
    
  // equation showing remainder
    remainderEq = i1 / i2;
    cout << "Result of division " << i1 << "/" << i2 << " is "
    << remainderEq << " R " << i1%i2 << ".";
    cout << endl; // space in between
    cout << "Thanks, and good bye." << endl;
    
  return 0;
 }
