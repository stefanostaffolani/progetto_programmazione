//#include <iostream>
#include <ncurses.h>
//#include "Platform.hpp"
//#include "Enemies.hpp"
#include "Field.hpp"
#include "Player.hpp"
//#include "Shoot.hpp"
//#include "Bonus.hpp"
using namespace std;

// dai cazzo

int len_list(p_bullet head){
        if(head == NULL) return 0;
        else{
                mvprintw(16,1,"head : counter = %d", head->counter);
                return 1 + len_list(head->next);
        }
}

int main(){
        srand(time(NULL));
	Field *field = new Field();
        Platform *p1 = new Platform();
        Bonus *b1 = new Bonus();
        Enemies* E = new Enemies();

        int lenS = field -> getLenS();
        int height = field -> getHeight();

        p1->addNode(height);
        b1->add_bonus(p1->get_current(), height);

        initscr();
        noecho();       // fa si che non si vede quello che premo dalla tastiera
        int ps = 0;     // pointer screen, mi dice dove sono, se vado a destra aumenta se vado a sinistra diminuisce
        int c;          // mi serve per immagazzinare quello che digito da tastiera
        p_bullet head = NULL;
        field->printField(ps);
        field->upgradeData(100,0);
        Player *player = new Player('@', p1, b1, 4, height);
        
        
        bool stop = false;
        curs_set(0);


        //(c = getch()) != 27

        // ciclo in cui di base avviene tutto
        while(!stop){ // 48 è il tasto 0, 27 tasto ESC 
                //cout << "char in posizione 2,2 " << mvinch(5,5)<< endl;
                // ... qua piazziamo codice tipo per i movimenti del giocatore o altre cose ... 
                //head = update_bullet_list(head)
                // mvprintw(16, 1, "head è NULL:");
                // mvprintw(18, 1, "lunghezza lista : %d", len_list(head));
                // if(head == NULL) mvprintw(16, 15, " y");
                // else {
                //         mvprintw(16, 15, " n");
                //         //if(head->counter > 11) head = NULL;        
                //         mvprintw(17, 1, "il counter di head è:%d", head->counter);
                //         // if(head->counter > 11) {
                //         //         head = NULL;
                //         // }
                // }
                timeout(100);
                player->print_item();
                //b1->printCash(ps, lenS, player->get_versor());
                c = getch();
                //mvprintw(20,1,"lunghezza lista %d", len_list(head));
                if(rand()%10 == 0){
                        b1->add_bonus(p1->get_current(), height);
                        b1->print_bonus(ps, lenS, player->get_versor());
                }
                p1 -> generate(height, lenS, ps, 50);
                field->printField(ps);
                // parte relativa alla stampa delle platform
                if (c == 27) stop = true;
                else if(c == 100){ // se premo d ->
                        player->set_versor(1);
                        player -> move(ps);//set_x(player->get_x() + 1);
                        
                } 
                else if(c == 32){      // premo space
                        //Q.enqueue(player->get_versor(), player->get_position());
                        head = add_bullet(head, player->get_position(), player->get_versor(), '-');
                }
                else if(c==119){
                        player->jump(ps, head);
                }
                else if(c == 97){ // se premo a <-
                        player->set_versor(-1);
                        player-> move(ps); //set_x(player->get_x() - 1);
                }
                int bonus = b1->find_bonus(ps, lenS, player->get_position().x, player->get_position().y);
                if(bonus == 0){ // trovato $
                        player->increase_points(10);
                        field->upgradeData(player->get_life(), player->get_points());
                        field->printField(ps);
                }
                else if(bonus == 1){ // trpvato V
                        if(player->get_life() + 10 < 100)
                                player->increase_life(10);
                        else
                                player->set_life(100);
                        field->upgradeData(player->get_life(), player->get_points());
                        field->printField(ps);        
                }
                
                if (head != NULL) print_bullet_list(head);
                p1->printPlatforms(ps, lenS, player->get_versor()); // chiama funzione che gestisce il print delle platform
                player->gravity(ps, head);
                if(player->is_hit()) mvprintw(20,1,"colpito");
                move(0,0);      // leva il cursore fuori dai coglioni
        }
        //TODO:game over
        endwin();

        return 0;
}
