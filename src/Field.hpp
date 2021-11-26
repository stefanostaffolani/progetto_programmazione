#include "Player.hpp"

class Field{
public:
	Field();
	void printField(int);
	void upgradeData(int, int);
	void gameOver();

	int getLenS();
	int getHeight();
	int getPoint();
	int getLife();
	
protected:
	int life;
	int points;
	
	int lenS; // length screen
	int height; // height of the screen
};
