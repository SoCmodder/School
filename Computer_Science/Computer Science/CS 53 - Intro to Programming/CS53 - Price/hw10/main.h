/* programmer: robertoMurillo    date: 11/11/05 *
 * file: main.h                  class: cs53    *
 * purpose: using classes.                      */

#ifndef MAIN_H
#define MAIN_H

/********** CLASS **********/

#include <iostream>
using namespace std;

// the user-defined constructor has all user-defined values.
// pre: none.
// post: all of the variables in the cat class are defined.

// the default constructor has all default values.
// pre: none.
// post: fills a cat with the default values.

// getName() allows access to the cat's name.
// pre: m_name must be declared.
// post: returns the name of the cat as a string.

// getAge() allows access to the cat's age.
// pre: m_age must be declared.
// post: the age of the cat is returned.

// getWeight() allows access to the weight of the cat.
// pre: m_weight must be declared.
// post: the weight is returned.

// getClaws() allows access to if the cat has claws or not.
// pre: m_hasClaws must be declared.
// post: whether the cat has claws or not is set to true or false.
// depending on if true or not, a string is output saying Yes or No.

// getColor() allows access to the color of the cat.
// pre: m_color must be declared.
// post: the color of the cat is returned.

// setName() sets the name to the string defined by the user.
// pre: a string must be sent to the function.
// post: sets m_name equal to the string entered by the user.

// setWeight() sets the weight equal to a float defined by the user.
// pre: a float must be sent to the function.
// post: sets m_weight equal to the float entered by the user.

// setClaws() sets the claws equal to true or false.
// pre: true or false value must be sent to the function.
// post: sets m_hasClaws equal to true or false.

// setAge() sets the age to a number defined by the user.
// pre: an integer must be sent to the function.
// post: sets m_age equal to the age declared by the user.

// speak() outputs the cat's meow.
// pre: none.
// post: outputs meow to the screen.

// operator < overloads the < operator for the cat class.
// pre: calling object must be declared as a cat.
// post: the < operator is overloaded and is given a true or false
//       value.

// operator >overloads the > operator for the cat class.
// pre: calling object must be declared as a cat.
// post: the > operator is overloaded and is given a true or false
//       value.

// operator == overloads the == operator for the cat class.
// Pre: calling object must be declared as a cat.
// Post: the == operator is overloaded and given a value of true or
//       false.

// operator >= overloads the >= operator for the cat class.
// pre: calling object must be declared as a cat.
// post: the >= operator is overloaded and given a value of true or
//       false.

// operator <= overloads the <= operator for the cat class.
// pre: calling object must be declared as a cat.
// post: the <= operator is overloaded and given a value of true or
//       false.

// operator != overloads the != operator for the cat class.
// pre: calling object must be declared as a cat.
// post: the != operator is overloaded and given a value of true or
//       false.

class Cat
{
  private:
    string m_name; // name of the cat.
    int m_age; // age of the cat.
    float m_weight; // weight of the cat.
    bool m_hasClaws; // if the cat has claws or not.
    bool m_isAlive; // if cat is alive or not.
    string m_color; // color of the cat.

  public:
    Cat( string name, int age, float weight, bool hasClaws, bool isAlive,
         string color );
    Cat();
    string getName()const;
    int getAge()const;
    float getWeight()const;
    string getClaws()const;
    string getAlive()const;
    string getColor()const;
    void setName( string name );
    void setWeight( float weight );
    void setClaws ( bool claws );
    void setAge ( int age );
    void speak();
    friend bool operator <( const Cat& lhs, const Cat& rhs );
    friend bool operator >( const Cat& lhs, const Cat& rhs );
    friend bool operator ==( const Cat& lhs, const Cat& rhs );
    friend bool operator >=( const Cat& lhs, const Cat& rhs );
    friend bool operator <=( const Cat& lhs, const Cat& rhs );
    friend bool operator != ( const Cat& lhs, const Cat& rhs );
};

/********** CLASS **********/

#endif
