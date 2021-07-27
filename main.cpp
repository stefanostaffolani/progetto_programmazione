#include <iostream>
#include <ncurses.h>
//#include "Platform.hpp"
#include "Field.hpp"
#include "Player.hpp"
#include "Bonus.hpp"
using namespace std;

// dai cazzo

int main(){
 
        srand(time(NULL));
	Field *field = new Field();
        Platform *p1 = new Platform();
        Bonus *b1 = new Bonus();

        int lenS = field -> getLenS();
        int height = field -> getHeight();

        p1->addNode(height);
        b1->addCash(p1->get_current(), height);

        initscr();
        noecho();       // fa si che non si vede quello che premo dalla tastiera
        int ps = 0;     // pointer screen, mi dice dove sono, se vado a destra aumenta se vado a sinistra diminuisce
        int c;          // mi serve per immagazzinare quello che digito da tastiera

        field->printField(ps);
        field->upgradeData(100,0);
        Player *player = new Player(lenS, height, p1->get_current());

        // ciclo in cui di base avviene tutto
        while((c = getch()) != 27){ // 48 è il tasto 0, 27 tasto ESC 
                // ... qua piazziamo codice tipo per i movimenti del giocatore o altre cose ... 
                if(rand()%10 == 0)
                        b1->addCash(p1->get_current(), height);

                p1 -> generate(height, lenS, ps, 50);
                field->printField(ps);
                // parte relativa alla stampa delle platform
                if(c == 100){ // se premo d ->
                        if (player -> get_x() + 20 > lenS) 
                                ps++;
                        else 
                                player -> set_x(player->get_x() + 1);
                        player->set_versor(1);
                        player->gravity();
                }
                else if(c==119){
                        player->collision_jump();
                }
                else if(c == 97 && ps >= 0){ // se premo a <-
                        if (player -> get_x() - 20 < 0) 
                                ps--;
                        else
                                player -> set_x(player->get_x() - 1);
                        player->set_versor(-1);
                        player->gravity();
                }
                //player->gravity();
                player->update_platform();
                player->printPlayer();        
                if(b1->findCash(ps, lenS, player->get_x(), player->get_y())){
                        field->upgradeData(field->getLife(), field->getPoint() + 10);
                        field->printField(ps);

                        // soluzione alquanto bruttina ma dio mio
                        for(int i = 0; i < 100; i++)
                        mvprintw(player->get_y(), i, " ");
                }
                

                b1->printCash(ps, lenS, player->get_versor());
                p1->printPlatforms(ps, lenS, player->get_versor()); // chiama funzione che gestisce il print delle platform
                move(0,0);      // leva il cursore fuori dai coglioni
        }
        
        endwin();

        return 0;
}
