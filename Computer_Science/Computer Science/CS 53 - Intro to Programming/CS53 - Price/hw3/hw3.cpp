// programmer: robertoMurillo   date: 09/11/05
// file: hw3.cpp
// purpose: adding a menu to ease the lives of all the boys and girls
   
  #include <iostream>
  #include <iomanip>
  using namespace std;

  int main()
  {
    // VARIABLES
    const float VEG_PRICE = 4.00;
    const float DORM_COST = 55.32;
    const float MEAT_COST = 5.00;
    
    bool quitFlag = false;
    float Price = 0;
    int mainChoice = 0, foodChoice = 0, numTable;
    // mainChoice means the number chosen in the Main Menu.
    // foodChoice means the number chosen in each of the Food menus.
  
  
    // MAIN MENU
    cout << "MAIN MENU" << endl;
    cout << "1.)  Vegetarian" << endl;
    cout << "2.)  Meatatarian" << endl;
    cout << "3.)  Dormfoodatarian" << endl;
    cout << "4.)  Quit" << endl;
    cout << endl; // space in between to make it look smoother.
    cout << "Please enter your choice: ";
    cin >> mainChoice;
    
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    
    // VEGETARIAN MENU
    if (mainChoice == 1)
      {
      Price = VEG_PRICE;
      
      cout << "Vegetarian Menu:" << endl;
      cout << "1.)  Grass" << endl;
      cout << "2.)  Leaves" << endl;
      cout << "3.)  Hay" << endl;
      cout << "4.)  Quit" << endl;
      cout << endl;
      cout << "Please choose 1-4:";
      cin >> foodChoice;
      cout << endl;
                                               
        if ( foodChoice == 1 )
          {
          cout << "Please enter your table number: ";
          cin >> numTable;
          cout << endl;
          cout << "Your food choice was Grass." << endl;
          cout << "Your table number is " << numTable << " and your price"
               << " is $" << Price << "." << endl;
          }                             
                                       
        else if ( foodChoice == 2 )
          {
          cout << "Please enter your table number: ";
          cin >> numTable;
          cout << endl;
          cout << "Your food choice was Leaves." << endl;
          cout << "Your table number is " << numTable << " and your price"
               << " is $" << Price << "." << endl;
          }
                                       
        else if ( foodChoice == 3 )
          {
          cout << "Please enter your table number: ";
          cin >> numTable;
          cout << endl;
          cout << "Your food choice was Hay." << endl;
          cout << "Your table number is " << numTable << " and your price"
               << " is $" << Price << "." << endl;
          }
          
        else if ( foodChoice == 4 )
          cout << "Thank you and have a good day." << endl;
          quitFlag;
      }
      
    // MEATATARIAN MENU
    else if (mainChoice == 2)
      {
        Price = MEAT_COST;
        
        cout << "Meatatarian Menu:" << endl; 
        cout << "1.)  Burgers" << endl;
        cout << "2.)  Pork Chops" << endl;
        cout << "3.)  Nuggets" << endl;
        cout << "4.)  Hotdogs" << endl;
        cout << "5.)  Quit" << endl;
        cout << endl;
        cout << "Please choose 1-5: ";
        cin >> foodChoice;
        cout << endl;
     
          if ( foodChoice == 1 )
            {
            cout << "Please enter your table number: ";
            cin >> numTable;
            cout << "Your have chosen Burgers." << endl;
            cout << "Your table number is " << numTable << " and your price "
                 <<  "is $" << Price << "." << endl;
            }
            
          else if ( foodChoice == 2 )
            {
            cout << "Please enter your table number: ";
            cin >> numTable;
            cout << "Your have chosen Pork Chops." << endl;
            cout << "Your table number is " << numTable << " and your price "
                 <<  "is $" << Price << "." << endl;
            }
          
          else if ( foodChoice == 3 )
            {
            cout << "Please enter your table number: ";
            cin >> numTable;
            cout << "Your have chosen Nuggets." << endl;
            cout << "Your table number is " << numTable << " and your price "
                 <<  "is $" << Price << "." << endl;
            }

          else if ( foodChoice == 4 )
            {
            cout << "Please enter your table number: ";
            cin >> numTable;
            cout << "Your have chosen Hot Dogs." << endl;
            cout << "Your table number is " << numTable << " and your price "
                 <<  "is $" << Price << "." << endl;
            }
          
          else if ( foodChoice == 5 )
            cout << "Thank you and have a good day." << endl;
            quitFlag;
      }
    
    // DORMFOODATARIAN MENU
    else if ( mainChoice == 3 )
      {
        Price = DORM_COST;
        
        cout << "Dormfoodatarian Menu:" << endl;
        cout << "1.)  Platypus Beak" << endl;
        cout << "2.)  Chupacabra Teeth" << endl;
        cout << "3.)  Mane of Liger" << endl;
        cout << "4.)  Jackalope Horn" << endl;
        cout << "5.)  Potto Pie" << endl;
        cout << "6.)  Quit" << endl;
        cout << endl;
        cout << "Please choose 1-6: ";
        cin >> foodChoice;
        cout << endl;
        
          if ( foodChoice == 1 )
            {
            cout << "Please enter your table number: ";
            cin >> numTable;
            cout << "You have chosen Platypus Beak." << endl;
            cout << "Your table number is " << numTable << " and your price "
                 << "is $" << Price << "." << endl; 
            }

          else if ( foodChoice == 2 )
            {
            cout << "Please enter your table number: ";
            cin >> numTable;
            cout << "You have chosen Chupacabra Teeth." << endl;
            cout << "Your table number is " << numTable << " and your price "
                 << "is $" << Price << "." << endl; 
            }
            
          else if ( foodChoice == 3 )
            {
            cout << "Please enter your table number: ";
            cin >> numTable;
            cout << "You have chosen Mane of Liger." << endl;
            cout << "Your table number is " << numTable << " and your price "
                 << "is $" << Price << "." << endl; 
            }
            
          else if ( foodChoice == 4 )
            {
            cout << "Please enter your table number: ";
            cin >> numTable;
            cout << "You have chosen Jackalope Horn." << endl;
            cout << "Your table number is " << numTable << " and your price "
                 << "is $" << Price << "." << endl; 
            }
            
          else if ( foodChoice == 5 )
            {
            cout << "Please enter your table number: ";
            cin >> numTable;
            cout << "You have chosen Potto Pie." << endl;
            cout << "Your table number is " << numTable << " and your price "
                 << "is $" << Price << "." << endl; 
            }
          
          else if ( foodChoice == 6 )
            {
            cout << "Thank you and have a good day." << endl;
            quitFlag;
            }
      }
      
    // QUIT
    else if ( mainChoice == 4 )
      cout << "Thank you and have a good day." << endl;
   
    cout << endl;
    cout << "You can't sue us if you choke.  Just kidding.  But really,"
         << " don't sue us. \n"
         << "Thanks." << endl;
   
  return 0;
  }
