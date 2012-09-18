/*
* Author: Elliot Gross
* Date: 3/9/06
* Filename: mini4Func.cpp
* Instructor: Brian Sea
* Description: This program will create a program that allow
* the user to create, modify, breed, and delete creatures. 
*/

#include "mini4Func.h" //includes mini4Func.h
#include <iostream>
#include <string> // allows for the use of strings
#include <ctime>
#include <cstdlib>  // srand, rand

using namespace std;


animal list[MAX_SIZE];
int first, second;
animal a, p1, p2, kid;
int choice, choice1, choice2;



/*
 * Function: displayMenu
 * Arguments: None
 * Returns: None
 * PreConditions: None
 * Posconditions: None
 * Purpose: Displays the menu and executes choices on the menu 
 */
void displayMenu()
{
int count=0;

  do
  {
	
    cout << "1. Add creature to the list" << endl;
    cout << "2. Modify a creature currently in the list" << endl;
    cout << "3. Delete a creature from the list" << endl;
    cout << "4. Breed 2 creatures" << endl;
	cout << "5. Display Animal in the array" << endl;
	cout << "6. Quit" << endl;
    cout << "What would you like to do?" << endl;
    cin >> choice;
    // displays menu and sets their selection to choice
  
   
    switch (choice) // switch between menu choices
    { 
      case 1:
		addAnimal(a, count);
		displayAnimal(a);
		cout << endl;
		break;
      case 2:
		cout << "What creature do you want to modify" << endl;
		cin >> choice1;
		displayAnimal(a);
		cout << endl;
		modAnimal(list[choice1]);
		displayAnimal(a);
		cout << endl;
		break;	
      case 3:
		cout << "What creature do you want to delete " << endl;
		displayAnimal(list[choice1]);
		cin >> choice1;
		delAnimal(list[choice1], count);		
		count++;
		cout << endl;
		break;
	  case 4:
		//displayList(list[], count);
		cout << "What creature should be the first parent?" << endl;
		cin >> choice1;
		p1 = list[choice1];
		cout << "What creature should be the second parent?" << endl;
		cin >> choice2;
		p2 = list[choice2] ;
		breedAnimal(kid, p1, p2, count);
		cout << endl;
		break;
	  case 5:
		cout <<"What creature do you wish to see?" << endl;
		cin >> choice1;
		displayAnimal(list[choice1]);
		cout << endl;
		break;
	  case 6:
        return; // exits
      default:
		cout << "Unknown choice! Please pick again!" << endl;
		//error trapping for unknown choice
	}
  }while(choice != 6);    //exits when 6
  return;
}


/*
 * Function: modAnimal
 * Arguments: Animal - instance of an animal by reference
 * count - position of animal you wish to modify
 * Returns: None
 * PreConditions: There is room in the array
 * Posconditions: animal will be added to the array
 * Purpose: Adds an animal to the array 
 */
void addAnimal( animal & a, int &count )
{
	int order;

	cout << "Please enter the characteristics of your creature";
	cout << endl;
	cout << "First, please enter what species your creature is";
	cout << endl;
	cin  >> a.species;
	cout << "Next, please enter in the Lifespan of the creature";
	cout << endl;
	cin  >> a.lifespan;
	cout << "Now enter the constitution of your creature" << endl;
	cin  >> a.constitution;
	cout << "Next please choose the order of your creature(#)" << endl;
	cout << "1. Mammal 2. Bird 3. Reptile 4. Fish " 
		 <<	"5. Amphibian 6. Tunicate" << endl;
	cout << endl;
	cin  >> order;
	a.order = (order_type)order;
	cout << "What is the gender of your animal? "<< endl;
	cout << "0. Female 1. Male";
	cin  >> a.gender;
	list[count] = a;
	count ++;
	
	return;
}
/*
 * Function: modAnimal
 * Arguments: Animal array - list of all animals
 * count - position of animal you wish to modify
 * Returns: None
 * PreConditions: There is a animal in the array
 * Posconditions: animal will be modified
 * Purpose: Changes the parameters of existing animal in the array 
 */

void modAnimal (animal &a)
{
	int order;

	cout << "Please enter the characteristics of your creature";
	cout << endl;
	cout << "First, please enter what species your creature is";
	cout << endl;
	cin  >> a.species;
	cout << "Next, please enter in the Lifespan of the creature";
	cout << endl;
	cin  >> a.lifespan;
	cout << "Now enter the constitution of your creature" << endl;
	cin  >> a.constitution;
	cout << "Next please choose the order of your creature(#)" << endl;
	cout << "1. Mammal 2. Bird 3. Reptile 4. Fish " 
		 <<	"5. Amphibian 6. Tunicate" << endl;
	cin  >> order;
	a.order = (order_type)order;
	cout << "Do you want your creature to be male? 0. Female 1. Male";
	cin  >> a.gender;
	return;
	
}

/*
 * Function: greetings
 * Arguments: None
 * Returns: None
 * PreConditions: None
 * Posconditions: None
 * Purpose: Welcomes the user
 */
void greetings () //function definition of greetings
{
	cout <<  "Hi there! Welcome to the Super Breeding Program" << endl;
}

/*
 * Function: goodbye
 * Arguments: None
 * Returns: None
 * PreConditions: None
 * Posconditions: None
 * Purpose: Says goodbye to the user
 */
void goodbye()
{
	cout << "Thanks for using the Super Breeding Program!" << endl;
}



/*
 * Function: calcStats
 * Arguments: None
 * Returns: None
 * PreConditions: None
 * Posconditions: None
 * Purpose: Calculates random stats
 */
bool calcStats(const animal p1, const animal p2)
{
	bool rtn = true;
	int random = rand()%100;
	int fail = 25;
	if (p1.species != p2.species)
		fail += 10;
	if (p1.constitution > p2.constitution)
	{
		if ((p1.constitution - p2.constitution) > 2)
			fail += 10;

	}
	else
	{
		if ((p2.constitution - p1.constitution) > 2) 
			fail+=10;
	}
	if (random <= fail)
		rtn = false;


	return rtn;
}
/*
 * Function: delAnimal
 * Arguments: Animal - instance of an animal by reference
 * count - position of animal you wish to modify
 * Returns: None
 * PreConditions: There is room in the array
 * Posconditions: animal will be removed from the array
 * Purpose: Removes an animal from array 
 */
void delAnimal(animal &a, int &count)
{
	swap(list[count], list[count-1]);
	return;
}


/*
 * Function: breedAnimal
 * Arguments: Animal - instance of an animal by reference
 * animal p1 - parent1
 * animal p2 - parent2
 * count - position in the array
 * Returns: None
 * PreConditions: There is room in the array
 * Posconditions: Breeds 2 animals
 * Purpose: Creates offspring 
 */
bool breedAnimal(animal &a, animal p1, animal p2, int &count)
{
	string newname = "";
	int newnum;
	bool rtn = true;
	srand(time(NULL)); // seeds
	
	if(calcStats(p1,p2))// calls calc stats
	{
		if(p1.gender == p2.gender)
		{
			cout << "Sorry members of the same gender cannot breed"<< endl;
			rtn = false;
		}
		else if((p1.order == 3 && p2.order == 1) || 
				(p1.order == 3 && p2.order == 2) ||
				(p2.order == 3 && p1.order == 1) || 
				(p2.order == 3 && p1.order == 2) ||
				(p2.order == 3 && p1.order == 6) ||
				(p1.order == 3 && p2.order == 6))
		{ //talks about mixbreed with reptiles, amphib, fish
			rtn = false;
			cout << "Sorry breeding cannot occur" << endl << endl;
		}
		else if((p1.order == 3 && p2.order == 4) || 
				(p1.order == 3 && p2.order == 5) ||
				(p1.order == 3 && p2.order == 3) ||
				(p2.order == 3 && p1.order == 4) || 
				(p2.order == 3 && p1.order == 5) ||
				(p2.order == 3 && p1.order == 3))
		{
			rtn = true;
			cout << "MIXBREED" << endl;
		}
		else if(p1.order != p2.order)
		{
			rtn = false;
			cout << "Sorry breeding cannot occur diff. order" << endl;
		}
		
		if(rtn != false)
		{
			if(p1.gender == 0)
			{
				animal tmp;
				tmp = p1;
				p1 = p2;
				p2 = tmp;//swap
			}
			int first = p1.species.size()/2;
			cout << first << endl;
				newname = p1.species.erase(first, p1.species.size()/2);
			int second = p2.species.size()/2;
			newname += &p2.species[second];
			kid.species = newname;//name
			
			int random = rand()%7 - 3;
			kid.constitution = (p1.constitution + p2.constitution)/2 + random;
			if(kid.constitution > 5)
				kid.constitution = 5;
			else if(kid.constitution < 1)//constitutions
				rtn = false;
			
			if(p1.lifespan > p2.lifespan)
			{
				newnum = p1.lifespan - p2.lifespan;
				random = rand()%newnum + p2.lifespan;//random number
			}
			else
			{
				newnum = p2.lifespan - p1.lifespan;
				random = rand()%newnum + p1.lifespan;//random num
			}
			kid.lifespan = random;
			
			random = rand()%2;
			if(random == 0)
				kid.gender = 1; //gender male
			else
				kid.gender = 0;// gender female

			if((p1.order == 3 && p2.order == 4) ||
				(p2.order == 3 && p1.order == 4))
			{
				kid.order = p1.order; //chance of random order
				//between reptile and fish
			}

			else if((p1.order == 3 && p2.order == 5) ||
					(p2.order == 3 && p1.order == 5))
					//chance of random order
					//between reptile and amphibian
			{
				kid.order = p1.order;
			}
			else
				kid.order = p1.order;
		

			list[count] = kid;
			count++;
			if(rtn == true)
				displayAnimal(kid);  //shows offspring
			else
				cout << "The two animals were unable to breed" << endl;
		}
		
	}
	else
	{
		rtn = false;
		cout << "Sorry breeding failed." << endl << endl;
	}

		
	return rtn;
}

/*
 * Function: displayAnimal
 * Arguments: Animal - instance of an animal by reference
 * Returns: None
 * PreConditions: none
 * Posconditions: Displays animal
 * Purpose: Displays animal in the array
 */
void displayAnimal( animal a)
{
	if (a.species == "")
		cout << "DOESN'T EXIST" << endl;
	else
		cout << "Your new animals name is "<< a.species << endl;
	if (a.lifespan == 0)
		cout << "DOESN'T EXIST" << endl;
	else 
		cout << "It has a lifespan of : " << a.lifespan << endl;
	if (a.constitution == 0)
		cout << "DOESN'T EXIST" << endl;
	else if (a.constitution > 5)
	{
		a.constitution = 5;
		cout << "It has a constitution of: " << a.constitution << endl;
	}
	else if (a.constitution < 0)
		cout << "I'm sorry your creature is too weak and has died" << endl; 
	else 
		cout << "It has a constitution of: " << a.constitution << endl;
	if (a.order == 1)
		cout << "It is of the order of Mammal" << endl;
	else if (a.order == 2)
		cout << "It is of the order of Bird" << endl;
	else if (a.order == 3)
		cout << "It is of the order of Reptile" << endl;
	else if (a.order == 4)
		cout << "It is of the order of Fish" << endl;
	else if (a.order == 5)
		cout << "It is of the order of Amphibian" << endl;
	else if (a.order == 6)
		cout << "It is of the order of Tunicate" << endl;
	else 
		cout << "DOESN'T EXIST" << endl;
	if (a.gender == 0)
		cout << "Your animal is a Female" << endl;
	else if (a.gender == 1)
		cout << "Your animal is a Male" << endl;
	return;
}




