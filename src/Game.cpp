#include "Game.hpp"

Game::Game(){
    srand(time(NULL));
    this->p1 = new Platform();
    this->b1 = new Bonus(p1);
    this->field = new Field();
    this->s1 = new Shoot();
    position start = {4,12};
    this->E = new Enemies(p1);
    this->player = new Player('@',p1,b1,E,s1,start);
    this->ps = 0;   //scrren pointer
    this->gameOver = false;
}

void Game::game_loop(){   // ciclo di gioco
    init();
    while(!this->gameOver){
        timeout(100);
        this->kbd_input();
        this->game_print();
        this->game_check_enemy_collision();
        this->game_generate();
        this->game_bonus();
        this->game_dynamics();
    }
    this->field->gameOver();
    endwin();
}

void Game::game_print(){
    this->s1->update_bullet(this->ps);
    this->E->check_is_hit(this->ps, s1);
    this->player->check_is_hit();    // se viene preso da un bullet nemico
                
    this->field->upgradeData(this->player->get_life(), this->player->get_points());
    this->field->printField(this->ps);          // stampa lo schermo e la legenda
                                
    this->p1->printPlatforms(this->ps, this->player->get_versor());
    this->b1->print_bonus(this->ps, this->player->get_versor());
    this->E->printEnemies(this->ps, this->player->get_versor());
}

void Game::game_generate(){
    // generazione di bonus, platform, enemies ----------------------
    this->p1->generate(this->ps, 50);
    this->b1->generate(10, this->ps);
    this->E->generate(5, this->ps);
    // --------------------------------------------------------------
}

void Game::game_dynamics(){
// aggiornamento dinamiche di gioco
    this->E->move_and_shoot(this->ps, this->player->get_position().x, s1);
    this->player->gravity(this->ps);
    this->E->increase_difficulty(this->ps);
}

void Game::game_check_enemy_collision(){
     //se sono sopra ad un nemico
    if(this->player->hit_enemy()) {
        this->player->decrease_life(10);
        this->E->delete_base_enemy(this->player->get_position(), this->ps);
    }
    this->player->print_item(0);          // stampa player @
}

void Game::game_bonus(){
    // verifica che il bonus sia stato incontrato e aggiorna valori vita / punti
    int type = this->b1->find_bonus(ps, this->player->get_position().x, this->player->get_position().y, this->player->get_versor());
    if(type == 0){         // ( $ )
            this->player->increase_points(10);
    }
    else if(type == 1){    // ( V )
        if(this->player->get_life() + 10 < 100)
            this->player->increase_life(10);
        else
            this->player->set_life(100);      
    } // ---------------------------------------------------------

}

void Game::kbd_input(){
    this->c = getch();    
    // verifica di che valore ottiene c da tastiera -----------------
    if (c == 27 || this->player->get_life() <= 0) this->gameOver = true;
    else if(c == (int)'d'){      // (d)     => destra       
        this->player->set_versor(1);
        this->player->move(ps);//set_x(player.get_x() + 1);          
        } 
    else if(c == (int)'a'){       // (a)     => sinistra
        this->player->set_versor(-1);
        this->player->move(ps); //set_x(player.get_x() - 1);
        }
    else if(c==(int)'w')        // (w)      => Salto
        this->player->jump(ps);
    else if(c == (int)' ')       // (SPACE) => sparo
        this->s1->add_bullet(this->player->get_position(), this->player->get_versor(), '-', P_DAMAGE);
}

void Game::init(){
    //genero 50 platform, 15 nemici e 15 bonus
    for(int i = 0; i < PLAT_INIT; i++)
        this->p1->addNode();
    for(int i = 0; i < BON_ENEM_INIT; i++){   //TODO: pulire sta cosa
        this->E->addNode(BON_ENEM_INIT);
        this->b1->addNode(BON_ENEM_INIT);
    }
    initscr();
    noecho();       // fa si che non si vede quello che premo dalla tastiera
    curs_set(0);    // rende invisibile il cursore
    field->upgradeData(LIFE,0);
}

