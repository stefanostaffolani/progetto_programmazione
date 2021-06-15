class Field{
public:
	Field();
	void printField(int ps);
	void upgradeData(int plLife, int plPoints);

	int getLenS() { return lenS; }
	int getHeight() { return height; }
	int getPoint() { return points; }
	int getLife() { return life; }
		
protected:
	int i;
	int life;
	int points;
	
	int lenS; // length screen
	int height; // height of the screen
};
