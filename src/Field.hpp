#include "Player.hpp"

class Field{
public:
	Field(){}
	void printField(int ps);
	void upgradeData(int plLife, int plPoints);
	void gameOver();

	int getPoint() { return points; }
	int getLife() { return life; }
		 
protected:
	int life;
	int points;
};
