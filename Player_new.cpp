#include <iostream>
#include <time.h>
#include <ncurses.h>
#include "Player_new.hpp"
#include <thread>
#include <chrono>

using namespace std;

Player::Player(){
    x = 1;
    y = 12;
    versor = 0;
}

void Player::set_versor(int i){this->versor = i;}

int Player::get_versor(){return this->versor;}

void Player::moveLeft() {
    if (this->x > 1) {
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

int Player::get_x() {
    return this->x;
}

int Player::get_y() {
    return this->y;
}

void Player::gravity(int x_platform_i, int x_platform_f, int y_platform){
    bool arrived;
    if ((this->x >= x_platform_i && this->x <= x_platform_f && (this->y == y_platform - 1)) || (this->y == 12)) arrived = true;
    else arrived = false;

    while(!arrived){
        mvdelch(this->y, this->x);
        this->y++;
        this->x = this->x + this->versor;
        mvaddch(this->y, this->x, '@');
        refresh();
        if ((this->x >= x_platform_i && this->x <= x_platform_f && (this->y == y_platform - 1)) || (this->y == 12)) arrived = true;
        std::this_thread::sleep_for(std::chrono::milliseconds (100));
    }
}


void Player::collision_jump(int x_platform_i, int x_platform_f, int y_platform){
    int x_player_f = this->x + (6 * this->versor);
    int y_player_f = this->y - 3;
    if ((y_player_f < y_platform) && (this->x < x_platform_i - 2 || this->x > x_platform_f + 2) && (x_player_f >= x_platform_i && x_player_f <= x_platform_f) && (y_player_f > 0) && (x_player_f > 1)){    // può atterrare sulla platform
        int i;
        for(i = 0; i < 3; i++){
            mvdelch(this->y, this->x);
            this->y--;
            this->x = this->x + this->versor;
            mvaddch(this->y, this->x, '@');
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds (100));
        }
        this->gravity(x_platform_i, x_platform_f, y_platform);
    }
    else {
        while(this->y > y_platform + 1 && this->x > 1){
            mvdelch(this->y, this->x);
            this->y--;
            this->x = this->x + versor;
            mvaddch(this->y, this->x, '@');
            refresh();
            //mvdelch(this->y, this->x);
            std::this_thread::sleep_for(std::chrono::milliseconds (100));
        }
        this->gravity(x_platform_i, x_platform_f, y_platform);
    }
}