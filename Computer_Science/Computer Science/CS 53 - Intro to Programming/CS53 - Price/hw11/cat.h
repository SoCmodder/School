/* programmer: Clayton Price          date: 11/26/05                  *
 * file: cat.h                                                        *
 * purpose: this file contains the function definitions of the member *
 *           functions of the cat class.                              */

#ifndef CAT_H
#define CAT_H

#include<string>
#include<iostream>

using namespace std;

// The constructors will initialize the cat objects

// The accessor (get) functions return the value of the associated member.
// Pre: none.
// Post: return value is the value of the associated member.

// The mutator (set) functions return nothing but set the value of the
// assoc'd member equal to the value passed. One exception: if wt passed
// to setwt function is negative, abs(wt) is set.
// Pre: none.
// Post: member variable is set to value passed.

// The speak function will output to the std out "meow".
// Pre: none.
// Post: "meow" output to std out (cout)

// The op << () function will output a cat in specified format if called.
// Pre: none.
// Post: a cat is output to the screen in the specified format.

// The op >> () function will extract a cat in specified format if called.
// Pre: file must be in right format.
// Post: a cat is input to the calling object in the specified format.

// The op == () function will return true if both cats are dead or if both
//    are alive and identical in all other aspects
// Pre: none.
// Post: true returned if calling obj and passed obj both dead or if both
//       alive
//    and all other attributes identical.

// The op != () returns negation of op == ().
// Pre: none.
// Post: opposite of Post for == operator.

// The op < () returns true if calling cat is dead and passed cat is
// alive, if both cats are alive and calling cat has no claws but passed
// cat does, if both cats are alive and both cats have or don't have claws
// and if the ratio of age to wt is less for calling cat than passed cat.
// Pre: none.
// Post: returns bool value described in function description.

// The operators <=, >, >= are defined in terms of < operator and ==
// operator.
// Pre: none.
// Post: returns bool value determined by the rules set out in the fnctn
//    description for operator <.

class dog;

class cat
{
  public:
    cat():m_name("cat"),m_age(1),m_wt(10),m_hasClaws(true),
          m_isAlive(true), m_color("calico"), m_type(1){}
    cat(string name,unsigned int age,float wt,bool clawed,
        bool alive = true, string color = "calico", int type = 1):
        m_name(name),m_age(age),m_wt(wt),m_hasClaws(clawed),
        m_isAlive(alive),m_color(color),m_type(type){}

    string getname()const {return m_name;}
    unsigned int getage()const {return m_age;}
    float getweight()const {return m_wt;}
    bool getclaws()const {return m_hasClaws;}
    bool getlife()const {return m_isAlive;}
    int gettype()const {return m_type;}
    string getcolor()const {return m_color;}

    void setname(const string name){m_name = name;}
    void setweight(const float wt){m_wt=(wt<0?-wt:wt);}
    void setclaws(const bool c){m_hasClaws = c;}
    void setage(const unsigned int age){m_age = age;}
    void setdead(){m_isAlive = false;}

    friend class shelter;

    void speak()const;

    friend ostream& operator <<(ostream & o, const cat cat1);
    friend istream& operator >>(istream & in, cat & cat1);
    bool operator == (const cat& rhs)const;
    bool operator != (const cat& rhs)const;
    bool operator < (const cat& rhs)const;
    bool operator <= (const cat& rhs)const;
    bool operator > (const cat& rhs)const;
    bool operator >= (const cat& rhs)const;

  private:
    string m_name;
    unsigned int m_age;
    float m_wt;
    bool m_hasClaws;
    bool m_isAlive;
    string m_color;
    int m_type;
};

#endif




