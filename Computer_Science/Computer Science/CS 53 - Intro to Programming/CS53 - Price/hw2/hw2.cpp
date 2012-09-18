/* programmer: robertoMurillo   date: 083105
   file: hw2.cpp   class: cs53 
   purpose: MORONICC formula for determing memory allocation. */
   
  #include <iostream>
  using namespace std;

  int main()

{

// defining variables
  int vowel, conso, kollar, mem;
  const float grav = 9.98;
  const float II = 3.14159;

// user-friendly output
  cout << "Hello.  Please take the time to fill out the following." << endl;
  cout << endl;            // space in between lines to make it look smooth.  
  
  cout << "Number of Vowels: ";
  cin >> vowel;
  
  cout << "Number of Consonants: ";
  cin >> conso;
  
  cout << "Color of shirt: ";
  cin >> kollar;
  
// final equation
  mem = static_cast<int>(( vowel/conso ) * (grav + II * kollar ) + 42);
  
  cout << endl;            // extra space in between to make it look pretty 
  cout << "Good luck with your computer." << endl;
  
  return 0;

}
