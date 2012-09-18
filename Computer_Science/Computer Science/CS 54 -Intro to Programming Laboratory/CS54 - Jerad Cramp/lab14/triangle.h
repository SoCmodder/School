/* programmer: robertoMurillo    date: 11/30/05 *
 * instructor: price             class: cs54d   *
 * file: triangle.h                             *
 * purpose: using templated classes             */
 
#ifndef TRIANGLE_H
#define TRIANGLE_H

/********** CLASS **********/

template <class T, class U>
class rightTriangle
{
  public:
    rightTriangle(); // default constructor
    rightTriangle( T bottomLeg, U leftLeg ); // manip'd constructor
    T calcHyp( ); // calculates hypotenuse
    float calcArea( ); // calculates area
    T getBottomLeg( )const; // accessor that returns bottom leg
    U getLeftLeg( )const; // accessor that returns left leg
  
  private:
    T m_bottomLeg;
    U m_leftLeg;
};

/********** CLASS **********/

/********** TEMPLATE DEFINITIONS **********/

template <class T, class U>
rightTriangle<T,U>::rightTriangle( T bottomLeg, U leftLeg )
{
  m_bottomLeg = bottomLeg;
  m_leftLeg = leftLeg;
}

template <class T, class U>
T rightTriangle<T,U>::calcHyp( )
{
  T hyp;
  
  // calculates the formula a^2 + b^2 = c^2
  hyp = sqrt(static_cast<double>((m_bottomLeg * m_bottomLeg) 
                                  + (m_leftLeg * m_leftLeg)));

return hyp;
}

template <class T, class U>
float rightTriangle<T,U>::calcArea( )
{
  float area;
  
  area = .5 * ( m_bottomLeg * m_leftLeg );
  
  return area;
}

template <class T, class U>
T rightTriangle<T,U>::getBottomLeg( )const
{
  return m_bottomLeg;
}

template <class T, class U>
U rightTriangle<T,U>::getLeftLeg( )const
{
  return m_leftLeg;
}

/********** TEMPLATE DEFINITIONS **********/

#endif
