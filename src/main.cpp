//#include "Shoot.hpp"
//#include "Bonus.hpp"
//#include "Enemies.hpp"
//#include <iostream>

#include <ncurses.h>
#include "Field.hpp"
#include "Player.hpp"
using namespace std;


int main(){

        srand(time(NULL));
	
        // genero oggeti per classi field platform e bonus
        Field *field = new Field();
        Platform *p1 = new Platform();
        Bonus *b1 = new Bonus(p1);

        // lenS -> lughezza schermo, height -> altezza schermo
        int lenS = field -> getLenS();
        int height = field -> getHeight();

        // genero oggetti Enemies e Player
        position start = {4,12};
        Enemies *E = new Enemies(p1, b1);
        Player *player = new Player('@', p1, b1, E, start);

        //genero 50 platform, 15 nemici e 15 bonus
        for(int i = 0; i < 50; i++)
                p1->addNode(height);
        for(int i = 0; i < 3; i++){
                E->addNode(5);
                b1->addNode(5);
        }

        p_bullet head = NULL;

        int ps = 0;             // pointer screen, mi dice dove sono, se vado a destra aumenta se vado a sinistra diminuisce
        int c;                  // mi serve per immagazzinare quello che digito da tastiera
        bool gameOver = false;   


        // ---------------------------------------------------------------------------------------------
        initscr();
        noecho();       // fa si che non si vede quello che premo dalla tastiera
        curs_set(0);    // rende invisibile il cursore

        field->upgradeData(100,0);      // aggiorna i dati vita e punti

        while(!gameOver){ // ciclo di gioco ===============================================
                
                timeout(100);      
                c = getch();    

                // verifica di che valore ottiene c da tastiera -----------------
                if (c == 27) gameOver = true;
                else if(c == 100){      // (d)     => destra       
                        player->set_versor(1);
                        player -> move(ps, head);//set_x(player->get_x() + 1);
                        
                } 
                else if(c == 97){       // (a)     => sinistra
                        player->set_versor(-1);
                        player-> move(ps, head); //set_x(player->get_x() - 1);
                }
                else if(c==119)        // (w)      => Salto
                        player->jump(ps, head);
                else if(c == 32)       // (SPACE) => sparo
                        head = add_bullet(head, player->get_position(), player->get_versor(), '-', P_DAMAGE);
                // ------------------------------------------------------------         
                

                // funzioni di stampa sullo schermo
                field->upgradeData(player->get_life(), player->get_points());
                field->printField(ps);          // stampa lo schermo e la legenda
                player->print_item(0);          // stampa player @
                p1->printPlatforms(ps, lenS, player->get_versor());
                b1->print_bonus(ps, lenS, player->get_versor());
                E->printEnemies(ps, lenS, player->get_versor(), player->get_position().x, head);


                // generazione di bonus, platform, enemies ----------------------
                p1->generate(height, lenS, ps, 50);
                b1->generate(10, lenS, ps);
                E->generate(5, lenS, ps);
                // --------------------------------------------------------------
                

                // verifica che il bonus sia stato incontrato e aggiorna valori vita / punti
                int type = b1->find_bonus(ps, lenS, player->get_position().x, player->get_position().y, player->get_versor());
                if(type == 0){         // ( $ )
                        player->increase_points(10);
                }
                else if(type == 1){    // ( V )
                        if(player->get_life() + 10 < 100)
                                player->increase_life(10);
                        else
                                player->set_life(100);      
                } // ---------------------------------------------------------

                // verifica che il nemico sia stato incontrato e aggiorna valori vita / punti
                type = E->find_enemy(ps, lenS, player->get_position().x, player->get_position().y);
                if(type == 0){
                        // ...
                }
                else if(type == 1){
                        // ...
                }

                // aggiornamento dinamiche di gioco
                E->move_and_shoot(lenS, ps, player->get_position().x, head);
                player->gravity(ps, head);
                if(player->is_hit()) player->decrease_life(15);      //TODO : far funzionare sta roba
                if(player->hit_enemy()) player->decrease_life(10);
                if (head != NULL) print_bullet_list(head, ps);
        
        } // fine ciclo di gioco ==========================================================
        //TODO:game over
        
        endwin(); // --------------------------------------------------------------------------------------

        return 0;
}



