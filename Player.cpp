#include <iostream>
#include <time.h>
#include <ncurses.h>
#include "Player.hpp"
#include <thread>
#include <chrono>

using namespace std;
 
Player::Player(int lenS, int height, p_node first, Platform* p1, Bonus* b1){
    x = lenS / 3; 
    y = height;  // 12
    versor = 1;
    life = 100;
    points = 0;
    printPlayer();
    initial = first;
    plat_dx = first;
    plat_sx = NULL;
    plat_cx = NULL;
    p2 = p1;
    b2 = b1;
    //len_screen = lenS; da vedere in futuro
}

int Player::get_life(){return this->life;}

int Player::get_points(){return this->points;}

void Player::increase_points(int n){this->points += n;}

void Player::update_platform(){
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

void Player::move(int& ps){
    if ((versor == -1) && (this->x > INIT_X)){
        mvprintw(this->y, this->x, " ");
        if(this->x < 20) ps--;
        else this->x--;
        mvprintw(this->y, this->x, PLAYER_AVATAR);
        refresh();
    }
    else if ((versor == 1) && (this->x < END_X)){
        mvprintw(this->y, this->x, " ");
        if(this->x > 55) ps++;
        else this->x++;    // check for length
        mvprintw(this->y, this->x, PLAYER_AVATAR);
        refresh();
    }
    p2->printPlatforms(ps, 75, this->versor);
    b2->printCash(ps, 75, versor);
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

void Player::jump(int& ps){
    int i = 0;
    bool hit_something = false;
    while((i < Y_JUMP) && !(hit_something)){
        if (mvinch(this->y - 1, this->x + versor) == 32){
            mvprintw(this->y, this->x, " ");
            this->y--;
            this->move(ps);
            i++;
        } else{
            hit_something = true;
        }
        update_platform(); // ci sta
        std::this_thread::sleep_for(std::chrono::milliseconds (100));
    }
    gravity(ps);
}

void Player::gravity(int& ps){
    bool hit_something = false;
    //int i = 0;
    if (mvinch(this->y + 1, this->x) != 32) hit_something = true;
    else hit_something = false;
    while(!(hit_something)){
        if(mvinch(this->y + 1, this->x + versor) != 32){
                hit_something = true;
                if (mvinch(this->y + 1, this->x + versor) == 36){
                    mvprintw(this->y, this->x, " ");
                    this->y++;
                    move(ps);
                    //increase_points(10);
                    //if (b2->findCash(ps, 75, this->x, this->y)) increase_points(10);
                } else if (mvinch(this->y + 1, this->x) == 32){
                    mvprintw(this->y, this->x, " ");
                    this->move(ps);
                }
            //fare il caso che tocca $ (numero 36) e vedere se ne servono altri
        } else{
            mvprintw(this->y, this->x, " ");
            this->y++;
            move(ps);
        }
        update_platform();    // ci sta
        std::this_thread::sleep_for(std::chrono::milliseconds (100));
    }
}
