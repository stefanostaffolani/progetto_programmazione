#include <ncurses.h>
#include "Field.hpp"
using namespace std;

Field::Field(){
	i = 1;
	// life = 0;
	// points = 0;
	
	height = 12;
	lenS = 75;
}

void Field::printField(int ps){	
	for (int i = 1; i <= lenS; i++){
		
		mvprintw(1,i,"-");
		if(i < height && ps == 0){
			mvprintw(i+1,0,"|");		
		}
		else if(ps > 0)
			mvprintw(i+1, 0, " ");

		mvprintw(height + 1,i,"-");
	}

	mvprintw(0,8,"LIFE:");
	mvprintw(0,35,"POINTS:");
}

void Field::upgradeData(int plLife, int plPoints){

	int i;
	//mvprintw(0,14, "   ");
	//mvprintw(0,44, "       ");
	
	for(i = 0; i < 8; i++){
		mvprintw(0,14 + i, " ");
		mvprintw(0,44 + i, " ");
		
	}


	life = plLife;
	points = plPoints;
	mvprintw(0,14, "%d",life);
	mvprintw(0,44, "%d",points);
}