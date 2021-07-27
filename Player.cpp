#include <iostream>
#include <time.h>
#include <ncurses.h>
#include "Player.hpp"
#include <thread>
#include <chrono>

using namespace std;
 
Player::Player(int lenS, int height, p_node first){
    x = lenS / 3; 
    y = height;  // 12
    versor = 1;
    printPlayer();
    plat_dx = first;
    plat_sx = NULL;
    plat_cx = NULL;
    //len_screen = lenS; da vedere in futuro
}

void Player::update_platform(){
    if(this->versor == 1){ // non ci sarà mai un caso NULL
        if(this->x >= plat_dx->x ){
            if(plat_cx != NULL) plat_sx = plat_cx->prev;
            plat_cx = plat_dx;
            plat_dx = plat_dx->next;
    } else if(this->x < (plat_dx->x + plat_dx->len) && plat_sx != NULL){
            plat_cx = plat_sx;
            plat_sx = plat_sx->prev;
            plat_dx = plat_dx->prev;
        }
    }
}

void Player::printPlayer(){
    mvprintw(this->y, this->x, "@");
    if(this->versor == -1)
        mvprintw(this->y, this->x + 1, " ");
    else if(this->versor == 1)
        mvprintw(this->y, this->x - 1, " ");
}

void Player::set_versor(int i){this->versor = i;}

int Player::get_versor(){return this->versor;}

void Player::moveLeft() {
    if (this->x > 1) {
        update_platform();
        mvdelch(this->y, this->x);
        this->x--;
        mvaddch(this->y, this->x, '@');
        refresh();
    }
}

void Player::moveRight() {
    if (this->x < 70) {
        mvdelch(this->y, this->x);
        this->x++;    // check for length
        mvaddch(this->y, this->x, '@');
        refresh();
    }
}

void Player::set_x(int n){ this->x = n; }

int Player::get_x() { return this->x; }

int Player::get_y() { return this->y; }

void Player::gravity(){  //TODO:remake this function...
    update_platform();
    int x_platform_i,x_platform_f,y_platform;
    if(versor == 1 && (plat_dx->x + plat_dx->x + plat_dx->len)/2 < this->x){
        x_platform_i = this->plat_dx->x;
        x_platform_f = this->plat_dx->x + this->plat_dx->len;
        y_platform = this->plat_dx->y;
    }else if (this->plat_sx != NULL){
        x_platform_i = this->plat_sx->x;
        x_platform_f = this->plat_sx->x + this->plat_sx->len;
        y_platform = this->plat_sx->y;
    }
    bool arrived;
    if ((this->x >= x_platform_i && this->x <= x_platform_f && (this->y == y_platform - 1)) || (this->y == 12)) arrived = true;
    else arrived = false;

    while(!arrived){
        mvprintw(this->y, this->x, " ");
        this->y++;
        this->x = this->x + this->versor;
	    if (this->y == y_platform && (this->x == x_platform_i || this->x == x_platform_f)){
		this->y--;
		mvaddch(this->y, this->x, '@');
		refresh();
		arrived = true;	
	    } else{
        	mvaddch(this->y, this->x, '@');
        	refresh();
        	if ((this->x >= x_platform_i && this->x <= x_platform_f && (this->y == y_platform - 1)) || (this->y == 12)) arrived = true;
	}
        std::this_thread::sleep_for(std::chrono::milliseconds (100));
    }
}


void Player::collision_jump(){
    update_platform();
    int x_platform_i,x_platform_f,y_platform;
    if(versor == 1 && !(this->x <= this->plat_dx->x+this->plat_dx->len && this->x >= this->plat_dx->x)){
        x_platform_i = this->plat_dx->x;
        x_platform_f = this->plat_dx->x + this->plat_dx->len;
        y_platform = this->plat_dx->y;
    }else if (this->plat_sx != NULL && !(this->x <= this->plat_sx->x+this->plat_sx->len && this->x >= this->plat_sx->x)){
        x_platform_i = this->plat_sx->x;
        x_platform_f = this->plat_sx->x + this->plat_sx->len;
        y_platform = this->plat_sx->y;
    }
    int x_player_f = this->x + (6 * this->versor);
    int y_player_f = this->y - 3;
    if ((y_player_f < y_platform) && (this->x < x_platform_i - 2 || this->x > x_platform_f + 2) && (x_player_f >= x_platform_i && x_player_f <= x_platform_f) && (y_player_f > 0) && (x_player_f > 1)){    // può atterrare sulla platform
        int i;
        for(i = 0; i < 3; i++){
            mvprintw(this->y, this->x, " ");
            this->y--;
            this->x = this->x + this->versor;
            mvaddch(this->y, this->x, '@');
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds (100));
        }
        this->gravity();
    }
    else {
        while(this->y > y_platform + 1 && this->x > 1){
            mvprintw(this->y, this->x, " ");
            this->y--;
            this->x = this->x + versor;
            mvaddch(this->y, this->x, '@');
            refresh();
            //mvdelch(this->y, this->x);
            std::this_thread::sleep_for(std::chrono::milliseconds (100));
        }
        this->gravity();
    }
}