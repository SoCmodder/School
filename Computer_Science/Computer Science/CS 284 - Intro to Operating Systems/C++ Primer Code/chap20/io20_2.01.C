#include <iostream.h>
#include <string>

/**
 **

 Please enter the item_number, item_name, and price: 
 10247 widget 19.99
 The values entered are: item# 10247 widget @$19.99

 Please enter the item_number, item_name, and price: 
 10247
  widget
 19.99
 The values entered are: item# 10247 widget @$19.99

 **/

int main() 
{
    int item_number;
    string item_name;
    double item_price;

    cout << "Please enter the item_number, item_name, and price: "
         << endl;

    cin >> item_number;
    cin >> item_name;
    cin >> item_price;

    cout << "The values entered are: item# " 
	 << item_number << " " 
 	 << item_name << " @$" 
 	 << item_price << endl;

}
