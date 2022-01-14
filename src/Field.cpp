#include <ncurses.h>
#include <iostream>
#include "Field.hpp"

using namespace std;

Field::Field(){}  //costruttore default

// stampa i contorni dello schermo con il punteggio e la vita
void Field::printField(int ps){	

	for(int i = 1; i <= LENGTH; i++){
		mvprintw(1,i,"-");				// stampo ------ sulla linea y = 1
		mvprintw(HEIGHT + 1,i,"-");		// srampo ------ sulla linea y = HEIGHT + 1
	}
	for(int i = 2; i <= HEIGHT; i++){	
		if(ps == 0) mvprintw(i, 0, "|");	// stampo il muro '|' a inizio schermo se ps è uguale a 0 
		else 		mvprintw(i, 0, " ");	// cancello l'eventuale muro se ps è maggiore di 0
	}		


	// cancella i precedenti valori numerici stampati
	for(int i = 0; i < 8; i++){
		mvprintw(0,14 + i, " ");
		mvprintw(0,44 + i, " ");	
	}

	// stampa target life e points
	mvprintw(0,8,"LIFE:");
	mvprintw(0,14, "%d",life);
	mvprintw(0,35,"POINTS:");
	mvprintw(0,44, "%d",points);
}

// aggiorna i valori vita e punteggio
void Field::upgradeData(int plLife, int plPoints){
	life = plLife;
	points = plPoints;
}

// stampa un avviso di game over e mostra il punteggio ottenuto
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

int Field::getPoint(){ return this->points; }
int Field::getLife(){ return this->life; }
