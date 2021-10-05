#include <ncurses.h>
#include <iostream>
#include "Field.hpp"
using namespace std;

Field::Field(){
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

	for(int i = 0; i < 8; i++){
		mvprintw(0,14 + i, " ");
		mvprintw(0,44 + i, " ");	
	}

	mvprintw(0,14, "%d",life);
	mvprintw(0,44, "%d",points);
}

//
void Field::upgradeData(int plLife, int plPoints){
	life = plLife;
	points = plPoints;
}

void Field::gameOver(){
	clear();
	mvprintw(2, 0, "  _____ _____ _____ _____    _____ _____ _____ _____ \n |   __|  _  |     |   __|  |     |  |  |   __| __  |\n |  |  |     | | | |   __|  |  |  |  |  |   __|    -|\n |_____|__|__|_|_|_|_____|  |_____| ___/|_____|__|__|\n");
	mvprintw(1, 20, "PRESS ESC TO EXIT");
	mvprintw(8, 23, "POINTS: %d", points);
	
	
	char c;
	do{
		c = getch();
	}while(c != 27);

}


