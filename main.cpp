#include <iostream>
#include <ncurses.h>
#include "Platform.hpp"
#include "Field.hpp"
using namespace std;

// dai cazzo

int main(){

        srand(time(NULL));
	Field *field = new Field();
        Platform *p1 = new Platform();

        int lenS = field -> getLenS();
        int height = field -> getHeight();

        p1->addNode(height);

        initscr();
        noecho();       // fa si che non si vede quello che premo dalla tastiera
        int ps = 0;     // pointer screen, mi dice dove sono, se vado a destra aumenta se vado a sinistra diminuisce
        int c;          // mi serve per immagazzinare quello che digito da tastiera

        // ciclo in cui di base avviene tutto
        while((c = getch()) != 27){ // 48 è il tasto 0, 27 tasto ESC 
                clear();        // mi pulisce lo schermo
                // ... qua piazziamo codice tipo per i movimenti del giocatore o altre cose ... 
        	
                        p1 -> generate(height, lenS, ps, 50);

                        field->printField(ps);
			field->upgradeData(100,0);
                // parte relativa alla stampa delle platform
                if(c == 100) // se premo d ->
                        ps++;
                else if(c == 97 && ps > 0) // se premo a <-
                        ps--;
                p1->printPlatforms(ps, lenS);         // chiama funzione che gestisce il print delle platform
                // mvprintw(10, 10, "S"); // a caso, è per stampare l'omino in basso ma forse andrà gestito da un altra parte  
                move(0,0);      // leva il cursore fuori dai coglioni

                /*
					

			field->upgradeData(95,0);

                */
        }
        
        endwin();

        return 0;
}
