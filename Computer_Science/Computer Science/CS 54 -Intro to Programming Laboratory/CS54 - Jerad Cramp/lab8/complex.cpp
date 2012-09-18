/* programmer: robertoMurillo  date: 10/12/05 *
 * instructor: price           class: cs54d   *
 * file: complex.cpp                          *
 * purpose: contains functions used by        *
 *          driver.cpp                        */
 
#include "complex.h"
#include <iostream>
using namespace std;

/*************** FUNCTION DEFINITIONS ***************/

// prints the final complex number in real +- imaginary form
void complex_print ( string sStatement, const complex & com1 )
{
  cout << sStatement << com1.m_numReal;
  if ( com1.m_numImaginary >= 0 ) // checks to see if the imaginary is positive
                                  // and adds a plus sign if it is
    cout << "+";
    
  cout << com1.m_numImaginary << "i" << endl; // adds the i onto the end

return;
}

// reads the input of the user
void complex_read( complex & com1 )
{
  cout << "Please enter in the real number portion: ";
  cin >> com1.m_numReal;
  cout << endl
       << "Please enter in the imaginary number portion: ";
  cin >> com1.m_numImaginary;

return;
}

// calculates the sum of the two complex numbers
complex complex_add( const complex & com1, const complex & com2 )
{
  complex addTotal; // complex number containing the sums of the real
                    // portion and imaginary portion
  // adds the two imaginary numbers  
  addTotal.m_numImaginary = com1.m_numImaginary + com2.m_numImaginary;
  // adds the two real numbers
  addTotal.m_numReal = com1.m_numReal + com2.m_numReal; 

return addTotal;
}

// calculates difference of two complex numbers
complex complex_sub( const complex & com1, const complex & com2 )
{
  complex subTotal; // complex number containing the difference of the real
                    // portion and imaginary portion
  // subtracts the two imaginary numbers
  subTotal.m_numImaginary = com1.m_numImaginary - com2.m_numImaginary;
  // subtracts the two real numbers
  subTotal.m_numReal = com1.m_numReal - com2.m_numReal;
  
return subTotal;
}

// calculates product of two complex numbers multiplied by each other
complex complex_mul( const complex & com1, const complex & com2 )
{
  complex mulTotal; // complex number containing the product of the real
                    // portion and imaginary portion
  // using FOIL method: multiplies Outsides and Insides and subtracts
  //                    Insides from Outsides
  mulTotal.m_numImaginary = (com1.m_numReal * com2.m_numImaginary)+
                            (com1.m_numImaginary * com2.m_numReal);
  // using FOIL method: multiplies First's and Lasts, then subtracts
  //                    Lasts from Firsts
  mulTotal.m_numReal = (com1.m_numReal * com2.m_numReal)-
                       (com1.m_numImaginary * com2.m_numImaginary);

return mulTotal;
}
/*************** FUNCTION DEFINITIONS ***************/
    
