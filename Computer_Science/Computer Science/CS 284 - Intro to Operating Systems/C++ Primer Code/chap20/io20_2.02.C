// #include <iostream>

#include <iostream.h>
#include <string>

/**
 ** ok: correct data entered:

  Please enter the item_number, item_name, and price: 
  10247 widget 19.99
  The values entered are: item# 10247 widget @$19.99

 ** oops: invalid data entered

  Please enter the item_number, item_name, and price: 
  widget 19.99 10247
  The values entered are: item# 0  @$1.06096e-314

 **/

int main()
{
    int item_number;
    string item_name;
    double item_price;

    cout << "Please enter the item_number, item_name, and price: "
         << endl;

    // ok: but potentially error-prone
    cin >> item_number >> item_name >> item_price;
    cout << "The values entered are: item# "
 	 << item_number << " "
 	 << item_name << " @$"
 	 << item_price << endl;
}

