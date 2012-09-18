/* programmer: robertoMurillo          date: 11/26/05                 *
 * file: dog.cpp                                                      *
 * purpose: this file contains the function definitions of the member *
 *           functions of the dog class.                              */

#include "dog.h"
#include <iostream>
#include<string>

using namespace std;

// The speak function will output to the std out "meow".
// Pre: none.
// Post: "bark" output to std out (cout)

void dog::speak()const
{
  cout<<"bark";
  return;
}

// The op == () function will return true if both dogs are dead or if both
//    are alive and identical in all other aspects
// Pre: none.
// Post: true returned if calling obj and passed obj both dead or if both
// alive and all other attributes identical.
// NOTE: This is good example of really cooool code that is extremely hard
// to read simply because I nested the ternary operator - a good example
// of what I told you not to do.  But it works. Nicely. Efficiently.

bool dog::operator == (const dog& rhs)const
{
  return m_isAlive != rhs.m_isAlive ? false : (!m_isAlive ? true :
         (m_name==rhs.m_name && m_age==rhs.m_age && m_wt==rhs.m_wt &&
          m_hasTeeth==rhs.m_hasTeeth && m_color==rhs.m_color));
}

// The op != () returns negation of op == ().
// Pre: none.
// Post: opposite of Post for == operator.

bool dog::operator != (const dog& rhs)const
{
  return !(*this == rhs);
}

// The op < () returns true if calling dog is dead and passed dog is
// alive, if both dogs are alive and calling dog has no teeth but passed
// dog does, if both dogs are alive and both dogs have or don't have teeth
// and if the ratio of age to wt is less for calling dog than passed dog.
// Pre: none.
// Post: returns bool value described in function description.

bool dog::operator < (const dog& rhs)const
{
  bool lessthan = false;            //default if calling obj is dead and
                                    //other is
                                    // alive OR both alive and calling obj
                                    // has no teeth
  if (!m_isAlive && rhs.m_isAlive)  // callin obj dead, other alive
    lessthan = true;
  else if (m_isAlive && rhs.m_isAlive)         // both alive
  {
    if ((!m_hasTeeth && !rhs.m_hasTeeth) || (m_hasTeeth
         && rhs.m_hasTeeth))
      lessthan = ((m_wt/m_age)<(rhs.m_wt/rhs.m_age));  // both w/ or w/o
                                                       // teeth
    else if (!m_hasTeeth && rhs.m_hasTeeth)    // both alive, caller w/o
                                               // teeth
      lessthan = true;
  }
  return lessthan;
}

// The operators <=, >, >= are defined in terms of < operator and ==
// operator.
// Pre: none.
// Post: returns bool value determined by the rules set out in the fnct.
//    description for operator <.

bool dog::operator <= (const dog& rhs)const
{
  return (*this < rhs || *this == rhs);
}

bool dog::operator > (const dog& rhs)const
{
  return (!(*this < rhs) && *this != rhs);
}

bool dog::operator >= (const dog& rhs)const
{
  return !(*this<rhs);
}

// The op << () function will output a dog in specified format if called.
// Pre: none.
// Post: a dog is output to the screen in the specified format.
ostream& operator <<(ostream & o, const dog dog1)
{
  o << dog1.m_name << "(a " << dog1.m_color << " ";
  switch(dog1.m_type)
  {
    case 1:
      cout << "toy poodle";
      break;
    case 2:
      cout << "doberman";
      break;
    case 3:
      cout << "coyote";
      break;
    case 4:
      cout << "wolf";
      break;
    case 5:
      cout << "hyena";
  }

  cout << "): " << "wt = " << dog1.m_wt << " age = " << dog1.m_age;
    if (dog1.m_hasTeeth)
      o << " has teeth and ";

    else
      o << " has no teeth and ";

    if (dog1.m_isAlive)
      o << "is alive." << endl;

    else
      o << "is dead." << endl;

  return o;
}

istream& operator >>(istream & in, dog & dog1)
{
  in >> dog1.m_name;
  in >> dog1.m_age;
  in >> dog1.m_wt;
  in >> dog1.m_hasTeeth;
  in >> dog1.m_isAlive;
  in >> dog1.m_color;
  in >> dog1.m_type;

  return in;
}

