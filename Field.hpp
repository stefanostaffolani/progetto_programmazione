class Field{
public:
	Field();
	void printField(int ps);
	void upgradeData(int plLife, int plPoints);

	int getLenS() { return lenS; }
	int getHeight() { return height; }
	int getPoint() { return points; }
	
	void setPoint(int n) { points += n; }
	
protected:
	int i;
	int life;
	int points;
	
	int lenS; // length screen
	int height; // height of the screen
};
