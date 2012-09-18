// programmer: robertoMurillo   date: 09/23/05
// file: hw4.cpp               
// purpose: ATM script for bob.

#include <iostream>
using namespace std;

int main()
{
  // DEFINED VARIABLES
  char cChoice;  // variable representing the user's decisions
  string sName;  // string for user's name
  int numAcct;   // user's own account
  int numAcct2;  // account of recipient
  double numTransact; // Amount you are dealing with
  bool validAcct = false;    // checks for account validity
  bool validChoice = false;  // checks for choice validity
  bool quit = false;         // quit flag

  // COLLECTING INFORMATION
  do
  {
    cout << "Please enter your first name: ";
    cin >> sName;
    do
    {
      cout << "Enter your account number: ";
      cin >> numAcct;

      if ( (numAcct/10000) == 11 || (numAcct/10000) == 22 )
        validAcct = true;
    } while (!validAcct);

    cout << "Thanks."
         << endl;

    cout << "D -- Deposit" << endl
         << "W -- Withdrawl" << endl
         << "T -- Legal Transfer" << endl
         << "E -- Embezzle" << endl
         << "Q -- Quit" << endl
         << endl
         << "Your choice: ";

    // CHOICES USING SWITCH-CASE
    do
    {
      cin >> cChoice;
      switch( cChoice )
      {
        // DEPOSIT
        case 'D':
        case 'd':
        case '1':
          do
          {
            cout << "How much would you like to deposit: ";
            cin >> numTransact;
          
            if ( numTransact >= 10000 )
            {
              cout << "Are you sure you would like to make a transaction"
                   << " for this large sum (y/n): ";
              cin >> cChoice;
          
              if ( cChoice == 'Y' || cChoice == 'y' )
              {  
                cout << "Thanks. Just checking!" << endl
                     << endl;  
              }
            }
          }while ( cChoice == 'N' || cChoice == 'n');
          
          cout << "$" << numTransact << " has been deposited in account"
               << " number " << numAcct << ".";
          break;
                                          
        // WITHDRAWAL
        case 'W':
        case 'w':
        case '2':
          do
          {
            cout << "How much would you like to withdrawal: ";
            cin >> numTransact;
          
            if ( numTransact >= 10000 )
            {
              cout << "Are you sure you would like to make a transaction"
                 << " for this large sum (y/n): ";
              cin >> cChoice;
                if ( cChoice == 'Y' || cChoice == 'y' )
                {
                  cout << "Thanks. Just checking!" << endl
                       << endl;
                }
            }
          }while ( cChoice == 'N' || cChoice == 'n');
            
          cout << "$" << numTransact << " has been withdrawn from account "
               << "number " << numAcct << ".";
          break;

        // TRANSFER
        case 'T':
        case 't':
        case '3':
          do
          {
          cout << "How much would you like to transfer: ";
          cin >> numTransact;
          
          if ( numTransact >= 10000 )
            {
            cout << "Are you sure you would like to make a transaction"
                 << " for this large sum (y/n): ";
            cin >> cChoice;
              if ( cChoice == 'Y' || cChoice == 'y' )
              {
                cout << "Thanks. Just checking!" << endl
                     << endl;
              }
            }
          }while ( cChoice == 'N' || cChoice == 'n');
                 
          do
          {
            validAcct = false;
            cout << "What account would you like to deposit this amount "
                 << "into: ";
            cin >> numAcct2;
                               
            if ( (numAcct2/10000) == 11 || (numAcct2/10000) == 22 )
              validAcct = true;
          } while (!validAcct);

          cout << "$" << numTransact << " has been transferred from "
               << "account " << numAcct << " to " << numAcct2 << ".";
          break;

        // EMBEZZLE
        case 'E':
        case 'e':
        case '4':
          do
          {
          cout << "How much would you like to embezzle: ";
          cin >> numTransact;
          
          if ( numTransact >= 10000 )
          {  
            cout << "Are you sure you would like to make a transaction"
                 << " for this large sum (y/n): ";
            cin >> cChoice;
              if ( cChoice == 'Y' || cChoice == 'y' )
              {
                cout << "Thanks. Just checking!" << endl
                     << endl;
              }
          }
          }while ( cChoice == 'N' || cChoice == 'n');
                                                                                                                                           
          do
          {
            validAcct = false;
            numAcct2 = false;
            cout << "What account would you like to deposit this amount"
                 << " into: ";
            cin >> numAcct2;
        
            if ( (numAcct2/10000) == 11 || (numAcct2/10000) == 22 )
              validAcct = true;
          } while(!validAcct);
        
          cout << "$" << numTransact << " has been embezzeled from "
               << "account " << numAcct << " to " << numAcct2 << ".";
        
          break;

        // QUIT
        case 'Q':
        case 'q':
        case '5':
          if (quit)
          {
            cout << "No transactions have been made.";
            quit = true;
          }
          break;

        default:
          cout << "That is not a valid choice.";
          break;
      }
    } while (validChoice);
    
    // ANOTHER TRANSACTION?
    cout << endl;
    cout << "Would you like to make another transaction (y/n): ";
    cin >> cChoice;
  } while (cChoice == 'y' || cChoice == 'Y');

return 0;
}
