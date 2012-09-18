/*
 * File: useSet.cpp
 * Description: a program that uses Set class
 */

#include <iostream>
#include "Set.h"

using namespace std;


// Start program execution here
int main()
{
int i;
Set s1("s1"), s2("s2"), s3("s3"), s4("s4");

  s1.print();

  for (i = 0; i <= 4; i++)
    s1.addElement(i * 2);
  cout << "Added even numbered elements to set " << s1.getName() << endl;
  s1.print();

  if (s1.isElementOf(2))
    cout << "2 IS an element of set " << s1.getName() << endl;
  else cout << "2 IS NOT an element of set " << s1.getName() << endl;

  if (s1.isElementOf(5))
    cout << "5 IS an element of set " << s1.getName() << endl;
  else cout << "5 IS NOT an element of set " << s1.getName() << endl;

  for (i = 1; i <= 5; i++)
    s2.addElement(i);
  cout << "\nAdded some elements to set " << s2.getName() << endl;
  s2.print();

  s2.deleteElement(3);
  s2.deleteElement(6);
  cout << "Deleted some elements from set " << s2.getName() << endl;
  s2.print();

  s3 = s1.set_union(s2);
  cout << "\nMade s3 the union of sets s1 and s2...\n";
  s3.setName("s3");
  s3.print();

  s3 = s1.set_intersection(s2);
  cout << "\nMade s3 the intersection of sets s1 and s2...\n";
  s3.setName("s3");
  s3.print();

  if (s4.isEmpty())
    cout << "Set " << s4.getName() << " IS empty!\n";
  else cout << "Set " << s4.getName() << " IS NOT empty!\n";

  cout << "\nPrinting set s4 before adding any elements...\n";
  s4.print();

  s4.addElement(100);
  s4.addElement(9);
  cout << "\nAdded some elements to set " << s4.getName() << endl;

  if (s4.isEmpty())
    cout << "Set " << s4.getName() << " IS empty!\n";
  else cout << "Set " << s4.getName() << " IS NOT empty!\n";

  cout << "\nPrinting set s4 after adding elements...\n";
  s4.print();

  s3 = s1.set_intersection(s4);
  cout << "\nMade s3 the intersection of sets s1 and s4...\n";
  s3.setName("s3");
  s3.print();

  return(0);
}
