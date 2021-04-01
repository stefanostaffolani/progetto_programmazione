#include <ncurses.h>
#include "Field.hpp"
using namespace std;

Field::Field(){
	i = 1;
	life = 0;
	points = 0;
}

void Field::printField(){
	initscr();
	noecho();
	
	for (int i = 1; i <= 75; i++){
		
		mvprintw(1,i,"-");
		if(i < 14){
			mvprintw(i+1,0,"|");		
		}

		mvprintw(15,i,"-");
	}

	mvprintw(0,8,"LIFE:");
	mvprintw(0,35,"POINTS:");

	/*mvprintw(0,14, (char[])life);
	mvprintw(0,14, (char[])points);*/
	endwin();
}

void Field::upgradeData(int plLife, int plPoints){

	initscr();
	noecho();
	mvprintw(0,14, "   ");
	mvprintw(0,44, "       ");


	life = plLife;
	points = plPoints;
	mvprintw(0,14, "%d",life);
	mvprintw(0,44, "%d",points);
	getch();
	endwin();
}