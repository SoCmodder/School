/* programmer: robertoMurillo     date: 091405
   file: lab4.cpp                 class: CS54d
   Instructor: Price
   Description: program strengthening if-else */

  #include <iostream>
  using namespace std;

  int main()
  {
    char carYear, carBrand;
    int Price = 0;
    
    cout << "Hello and welcome to Honest Al's Car Emporium!" << endl;
    cout << endl;           // space in between
    cout << "Would you prefer a new car, a used car or a classic? \n" 
         << "Please enter N, U, or C respectively: ";
    cin >> carYear;
    cout << endl;           // space in between
   
    cout << "Do you want an American car or a Japanese car? \n"
         << "Please enter A for American, J for Japanese, or D for" 
         << " don't care: ";
    cin >> carBrand;
    cout << endl;
    cout << "We have these cars for you:" << endl;
    
    if ( carYear == 'c' && ( carBrand == 'a' || carBrand == 'd' ))
    {
      cout << "A 1957 Chevy Belaire" << endl;
      Price = 5000; 
    }
   
    else
      if ( carYear == 'u' && ( carBrand == 'j' || carBrand == 'd' ))
      {
        cout << "A 1998 Honda Civic" << endl;
        Price = 1000;
      }

      else
        if ( carYear == 'n' && (carBrand == 'a' || carBrand == 'd' ))
        {
          cout << "A 2006 Ford Fiesta" << endl;
          Price = 20000;
        }
        
        else 
          if ( Price == 0 )
            cout << "There are no cars available at this time." << endl;
    
    cout << endl;       // space in between
    cout << "Thanks for shopping at Honest Al's!" << endl;

  return 0;
  }
