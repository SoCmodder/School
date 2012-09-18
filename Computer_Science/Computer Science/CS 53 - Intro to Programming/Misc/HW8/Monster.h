//Monster.h
//Matt Ludwikosky

#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <iomanip>
#include <string>
#include "GameEntity.h"
using namespace std;

class Monster : public GameEntity
{
public:
	string weapons;
	float healthRating;
public:
	enum Constant { MAX_WEAPONS_LENGTH = 25 };

	void setWeapons(const string theWeapons) { weapons = theWeapons; }
	string getWeapons() const { return(weapons); }
	void setHealthRating(const float theRating) { healthRating = theRating; }
	int getHealthRating() const { return(healthRating); }

	Monster() { weapons = "(No Weapons)"; healthRating = 0; }
	Monster(const string theName, const string theGame,
		const string theWeapons, const int theRating): GameEntity(theName, theGame) {
		weapons = theWeapons; healthRating = theRating; }

	friend istream& operator >>(istream& ins, Monster& m) {
	char c[MAX_WEAPONS_LENGTH];

	m.GameEntity::operator >>(ins);
	
	cout << "\nWeapons:";
	ins.getline(c, MAX_WEAPONS_LENGTH-1);
	m.weapons = c;
	cout << "\nHealth Rating:";
	ins >> m.healthRating;
	ins.get();

	return(ins);
	}

	friend ostream& operator <<(ostream& outs, Monster& m)
	{
    cout.unsetf(ios::right);
    cout.setf(ios::left);
  
    m.GameEntity::operator <<(outs);

    outs << setw(25) << setfill(' ') << m.weapons;
    outs << m.healthRating << endl;
    outs << setw(66) << setfill('_') << " " << endl;

    return(outs);
	}
};

#endif