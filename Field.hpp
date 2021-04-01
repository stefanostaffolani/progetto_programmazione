class Field{
public:
	Field();
	void printField();
	void upgradeData(int plLife, int plPoints);

	int getLenS() { return lenS; }
	int getHeight() { return height; }
	
protected:
	int i;
	int life;
	int points;
	
	int lenS; // length screen
	int height; // height of the screen
};
