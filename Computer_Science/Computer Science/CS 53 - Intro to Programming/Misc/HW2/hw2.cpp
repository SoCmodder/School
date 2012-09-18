//Matt Ludwikosky  CS53
//HW2 09/23/04
//Purpose: Take in snack bar orders using nested loops
#include <iostream>
using namespace std;

int main()
{
   //Initalize variables
   int item;
   char customer = 'y', order = 'y';
   float total;

   //Outer customer loop
   do
   {
	    //Reset total for each new customer
		total = 0.00;
		do
		{
			cout << "Which item would you like:" << endl;
			cout << "1. Hotdog\n2. Chips\n3. Soda" << endl;
			cin >> item;

			while(item < 1 || item > 3)
			{
				cout << "\nInvalid selection. Please enter 1-3:";
				cin >> item;
			}

			switch(item)
			{
				case 1:
					total += 1;
					break;
				case 2:
					total += 0.75;
					break;
				case 3:
					total += 0.85;
					break;
			}

			cout << "\nDo you want another item? (Y/N):";
			cin >> order;
			
		} while(order == 'y' || order == 'Y');

		total += (total * .07);
		cout << "\nYour total with tax is $" << total << endl;
		
		cout << "\nIs there another customer? (Y/N):";
		cin >> customer;

	} while(customer == 'y' || customer == 'Y');

   return 0;
}
