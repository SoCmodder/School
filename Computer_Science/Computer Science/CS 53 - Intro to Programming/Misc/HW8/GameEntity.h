//GameEntity.h
//Matt Ludwikosky

#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <iostream>
using namespace std;

#include <cstdlib>
#include <string>

class GameEntity
{
private:
	string game;
	string name;
public:
	enum Constants { MAX_NAME_LENGTH = 25, MAX_GAME_NAME_LENGTH = 10 };

	GameEntity() { game = "(No Game)"; name = "(No Name)"; }
	GameEntity(string theGame, string theName) { game = theGame; name = theName; }

	void setGame(const string theGame) { game = theGame; }
	string getGame() const { return(game); }
	void setName(const string theName) { name = theName; }
	string getName() const { return(name); }

	bool operator ==(const GameEntity& g);

	istream& operator >>(istream& ins) {
	char c[MAX_NAME_LENGTH];

		cout << "\nEnter game name:"; 
		ins.getline(c, MAX_GAME_NAME_LENGTH-1);
		game = c;
		cout << "\nEnter the name:";
		ins.getline(c, MAX_NAME_LENGTH-1);
		name = c;
		return(ins);
	}

	ostream& operator <<(ostream& outs) {
		outs << endl << setw(10) << setfill(' ') << game;
		outs << setw(25) << setfill(' ') << name;
		return(outs); }
};

bool GameEntity::operator ==(const GameEntity& g)
{
	return((name == g.name) && (game == g.game));
}

#endif