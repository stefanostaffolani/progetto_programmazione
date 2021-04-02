#include <ncurses.h>
#include "Field.hpp"
using namespace std;

Field::Field(){
	i = 1;
	life = 0;
	points = 0;
	
	height = 14;
	lenS = 75;
}

void Field::printField(int ps){
	initscr();
	noecho();
	
	for (int i = 1; i <= lenS; i++){
		
		mvprintw(1,i,"-");
		if(i < height && ps == 0){
			mvprintw(i+1,0,"|");		
		}

		mvprintw(height + 1,i,"-");
	}

	mvprintw(0,8,"LIFE:");
	mvprintw(0,35,"POINTS:");

	endwin();
}

void Field::upgradeData(int plLife, int plPoints){

	int i;
	
	initscr();
	noecho();
	//mvprintw(0,14, "   ");
	//mvprintw(0,44, "       ");
	
	for(i = 0; i < 8; i++){
		mvdelch(0,14 + i);
		mvdelch(0,44 + i);
		
	}


	life = plLife;
	points = plPoints;
	mvprintw(0,14, "%d",life);
	mvprintw(0,44, "%d",points);
	getch();
	endwin();
}
