#include <iostream>
#include <ncurses.h>
#include "Platform.hpp"
using namespace std;


int main(){

        Platform *p1 = new Platform();
        p1->addNode();

        initscr();
        noecho();       // fa si che non si vede quello che premo dalla tastiera
        int ps = 0;     // pointer screen, mi dice dove sono, se vado a destra aumenta se vado a sinistra diminuisce
        int c;          // mi serve per immagazzinare quello che digito da tastiera

        // ciclo in cui di base avviene tutto
        while((c = getch()) != 48){ // 48 è il tasto 0, 27 dovrebbe essere il tasto ESC ma non ho provato
                
                // ... qua piazziamo codice tipo per i movimenti del giocatore o altre cose ... 

                // parte relativa alla stampa delle platform
                if(c == 100) // se premo d ->
                        ps++;
                else if(c == 97 && ps > 0) // se premo a <-
                        ps--;
                clear();        // mi pulisce lo schermo, forse andrà spostato
                p1->printPlatforms(ps);         // chiama funzione che gestisce il print delle platform
                // mvprintw(10, 10, "S"); // a caso, è per stampare l'omino in basso ma forse andrà gestito da un altra parte  
                move(0,0);      // leva il cursore fuori dai coglioni
        }
        
        endwin();

        return 0;
}
