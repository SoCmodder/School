/*
* Author: Elliot Gross
* Date: 3/9/06
* Filename: mini4Func.h
* Instructor: Brian Sea
* Description: This program will create a program that allow
* the user to create, modify, breed, and delete creatures. 
*/

#ifndef MINI4FUNC_H
#define MINI4FUNC_H

#include <iostream>
using namespace std;


const int MAX_SIZE = 30;

enum order_type {MAMMAL =1, BIRD =2, REPTILE =3, FISH = 4, 
                AMPHIBIAN =5, TUNICATE =6};

struct animal //sets the struct
{
	string species;
    unsigned int lifespan;
    int constitution;
    order_type order;
    bool gender;
};





void greetings();
void displayMenu();
void addAnimal( animal & a, int &count );
void modAnimal (animal &a);
bool calcStats(const animal p1, const animal p2);
void delAnimal(animal &a, int &count);
bool breedAnimal(animal &a,  animal p1, animal p2, int &count);
void displayAnimal(animal a);
void goodbye();




#endif
