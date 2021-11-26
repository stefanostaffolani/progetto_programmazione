#include "Field.hpp"

int main(){

        srand(time(NULL));
	
        // genero oggeti per classi field platform bonus e shoot
        Field field;
        Platform p1;
        Bonus b1(&p1);
        Shoot s1;
 

        // lenS -> lughezza schermo, height -> altezza schermo
        int lenS = field.getLenS();
        int height = field.getHeight();

        // genero oggetti Enemies e Player
        position start = {4,12};
        Enemies E(&p1);
        Player player('@', &p1, &b1, &E, &s1, start);

        //genero 50 platform, 15 nemici e 15 bonus
        for(int i = 0; i < 50; i++)
                p1.addNode(height);
        for(int i = 0; i < 3; i++){   //TODO: pulire sta cosa
                E.addNode(5);
                b1.addNode(5);
        }

        int ps = 0;             // pointer screen, mi dice dove sono, se vado a destra aumenta se vado a sinistra diminuisce
        int c;                  // mi serve per immagazzinare quello che digito da tastiera
        bool gameOver = false;   


        // ---------------------------------------------------------------------------------------------
        initscr();
        noecho();       // fa si che non si vede quello che premo dalla tastiera
        curs_set(0);    // rende invisibile il cursore

        field.upgradeData(100,0);      // aggiorna i dati vita e punti

        while(!gameOver){ // ciclo di gioco ===============================================
                
                timeout(100);      
                c = getch();    

                // verifica di che valore ottiene c da tastiera -----------------
                if (c == 27 || player.get_life() <= 0) gameOver = true;
                else if(c == (int)'d'){      // (d)     => destra       
                        player.set_versor(1);
                        player.move(ps);//set_x(player.get_x() + 1);
                        
                } 
                else if(c == (int)'a'){       // (a)     => sinistra
                        player.set_versor(-1);
                        player.move(ps); //set_x(player.get_x() - 1);
                }
                else if(c==(int)'w')        // (w)      => Salto
                        player.jump(ps);
                else if(c == (int)' ')       // (SPACE) => sparo
                        s1.add_bullet(player.get_position(), player.get_versor(), '-', P_DAMAGE);
                // ------------------------------------------------------------         
                

                // funzioni di stampa sullo schermo
                s1.update_bullet(ps, lenS);
                E.check_is_hit(ps, lenS, &s1);
                player.check_is_hit();    // se viene preso da un bullet nemico
                
                field.upgradeData(player.get_life(), player.get_points());
                field.printField(ps);          // stampa lo schermo e la legenda
                                
                p1.printPlatforms(ps, lenS, player.get_versor());
                b1.print_bonus(ps, lenS, player.get_versor());
                E.printEnemies(ps, lenS, player.get_versor());
                
                
                //se sono sopra ad un nemico
                if(player.hit_enemy()) {
                        player.decrease_life(10);
                        E.delete_base_enemy(player.get_position(), ps);
                }
                player.print_item(0);          // stampa player @
                //-----------------

                // generazione di bonus, platform, enemies ----------------------
                p1.generate(height, lenS, ps, 50);
                b1.generate(10, lenS, ps);
                E.generate(5, lenS, ps);
                // --------------------------------------------------------------
                

                // verifica che il bonus sia stato incontrato e aggiorna valori vita / punti
                int type = b1.find_bonus(ps, lenS, player.get_position().x, player.get_position().y, player.get_versor());
                if(type == 0){         // ( $ )
                        player.increase_points(10);
                }
                else if(type == 1){    // ( V )
                        if(player.get_life() + 10 < 100)
                                player.increase_life(10);
                        else
                                player.set_life(100);      
                } // ---------------------------------------------------------

                // aggiornamento dinamiche di gioco
                E.move_and_shoot(lenS, ps, player.get_position().x, &s1);
                player.gravity(ps);
                E.increase_difficulty(ps);
                mvprintw(18,1,"ps=%d",ps);
                mvprintw(19,1,"difficoltà=%d", E.get_difficulty());
                
        } // fine ciclo di gioco ==========================================================
        
        field.gameOver();
        
        endwin(); // --------------------------------------------------------------------------------------

        return 0;
}



