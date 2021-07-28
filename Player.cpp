#include <iostream>
#include <time.h>
#include <ncurses.h>
#include "Player.hpp"
#include <thread>
#include <chrono>

using namespace std;
 
Player::Player(int lenS, int height, int& ps){
    x = lenS / 3; 
    y = height;  // 12
    versor = 1;
    pointer_screen = ps;
    printPlayer();
    //initial = p1;
    //plat_dx = p1;
    plat_sx = NULL;
    plat_cx = NULL;
    //len_screen = lenS; da vedere in futuro
}


void Player::update_platform(){   //REMINDER: potrebbe tornare utile se non serve si toglie alla fine
    if (this->versor == 1){
        if (this->x >= plat_dx->x){
            if (plat_cx == NULL){
                plat_cx = plat_dx;
                plat_dx = plat_dx->next;
            }
            else{
                plat_sx = plat_cx;
                plat_cx = plat_cx -> next;
                plat_dx = plat_dx -> next;
            }
        }
    }
    else{
        if (plat_cx != NULL){
            if(this->x < plat_cx->x){
                plat_dx = plat_dx->prev;
                plat_cx = plat_cx -> prev;
                if(plat_sx != NULL){
                    plat_sx = plat_sx->prev;
                }
            }
        }
    }
}

void Player::printPlayer(){
    mvprintw(this->y, this->x, PLAYER_AVATAR);
    if(this->versor == -1)
        mvprintw(this->y, this->x + 1, " ");
    else if(this->versor == 1)
        mvprintw(this->y, this->x - 1, " ");
}

void Player::set_versor(int i){this->versor = i;}

int Player::get_versor(){return this->versor;}

void Player::shoot(){     //TODO: testare questa funzione
    bool hit_something = false;
    int i = this->x+1;
    while((i <= RANGE) && !(hit_something)){  //TODO: far si che lo sparo entri sempre nello screen
        if(mvinch(this->y, i) != 32){
            hit_something = true;
        }
        else{
            mvprintw(this->y, i, BULLET);
            std::this_thread::sleep_for(std::chrono::milliseconds (100));
            mvprintw(this->y, i, " ");
            i++;    
        }
    }
}

void Player::move(Platform* p1){
    if ((versor == -1) && (this->x > INIT_X)){
        if (this->x < 20) pointer_screen--;
        else{
            mvprintw(this->y, this->x, " ");
            this->x--;
            mvprintw(this->y, this->x, PLAYER_AVATAR);
            refresh();
        }
    }
    else if ((versor == 1) && (this->x < END_X)){
        if(this->x > 55) pointer_screen++;
        else {
            mvprintw(this->y, this->x, " ");
            this->x++;    // check for length
            mvprintw(this->y, this->x, PLAYER_AVATAR);
            refresh();
        }
    }
    p1->printPlatforms(pointer_screen, 75, versor);
    //update_platform();
}

void Player::set_x(int n){ this->x = n; }

int Player::get_x() { return this->x; }

int Player::get_y() { return this->y; }

p_node Player::get_platdx(){
    return plat_dx;
}

p_node Player::get_platsx(){
    if (plat_sx == NULL)
        return plat_dx;
    else
        return plat_sx;
}

p_node Player::get_platcx(){
    if (plat_cx == NULL)
        return plat_dx;
    else
        return plat_cx;
}

void Player::jump(Platform* p1){
    int i = 0;
    bool hit_something = false;
    while((i < Y_JUMP) && !(hit_something)){
        if (mvinch(this->y - 1, this->x + versor) == 32){
            mvprintw(this->y, this->x, " ");
            this->y--;
            this->move(p1);
            i++;
        } else{
            hit_something = true;
        }
        //update_platform(); // ci sta
        std::this_thread::sleep_for(std::chrono::milliseconds (100));
    }
    gravity(p1);
}

void Player::gravity(Platform* p1){
    bool hit_something = false;
    //int i = 0;
    if (mvinch(this->y + 1, this->x) != 32) hit_something = true;
    else hit_something = false;
    while(!(hit_something)){
        if(mvinch(this->y + 1, this->x + versor) != 32){
            hit_something = true;
            if (mvinch(this->y + 1, this->x) == 32){
                mvprintw(this->y, this->x, " ");
                this->move(p1);
            }//fare il caso che tocca $ (numero 36) e vedere se ne servono altri
        } else{
            mvprintw(this->y, this->x, " ");
            this->y++;
            move(p1);
        }
        //update_platform();    // ci sta
        std::this_thread::sleep_for(std::chrono::milliseconds (100));
    }
}
