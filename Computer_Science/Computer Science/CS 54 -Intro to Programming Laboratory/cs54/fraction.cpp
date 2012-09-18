#include <iostream>
#include "fraction.h"
using namespace std;

CFraction::CFraction() : m_siNumer(1), m_siDenom(1)
{
}
void CFraction::readIn()
{
  cout<<"What is the numerator: ";
  cin>>m_siNumer;
  cout<<"What is the denominator: ";
  cin>>m_siDenom;
  cout<<endl;
  return;
 }
 
void CFraction::print()
 {
  cout<<m_siNumer<<"/"<<m_siDenom;
  return;
 }
 
CFraction CFraction::recipricol()
 {
  CFraction recip;
  recip.m_siNumer = m_siDenom;
  recip.m_siDenom = m_siNumer;
  return recip;
 }
 
short CFraction::getNumer () const
{
 return m_siNumer;
}

short CFraction::getDenom () const
{
 return m_siDenom;
}

void CFraction::setNumer(const short ksiVal)
{
 m_siNumer = ksiVal;
 return;
}

void CFraction::setDenom(const short ksiVal)
{
 m_siDenom = ksiVal;
 return;
}

void CFraction::unreduce(const short ksiNum)
{
 m_siNumer = m_siNumer*ksiNum;
 m_siDenom = m_siDenom*ksiNum;
}
