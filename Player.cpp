#include <iostream>
#include <time.h>
#include <ncurses.h>
#include "Player.hpp"

using namespace std;

Player::Player(){
    x = 0;
    y = 10;
}

void Player::moveLeft() {
    if (this->x > 0) this->x--;
    mvprintw(this->y, this->x, "@");
}

void Player::moveRight() {
    if (this->x < 70) this->x++;    // check for length
    mvprintw(this->y, this->x, "@");
}
//TODO: ask prof for chrono and remake delay
void Player::delay(float seconds) {
    float milliseconds = 1000000 * seconds;
    clock_t start_time = clock();
    bool stop = false;
    while (!stop){
        if (clock() > start_time + milliseconds) stop = true;
    }
}

int Player::get_x() {
    return this->x;
}

int Player::get_y() {
    return this->y;
}

//TODO: game's physics, this function only print the jump
void Player::jumpPlayer() {
    if (this->y > 3) {
        for(int i = 0; i < 4; i++){
            this->y--;
            refresh();
            clear();
            mvprintw(y, x, "@");
            this->delay(0.1);
        }

        for(int i = 0; i < 4; i++){
            this->y++;
            refresh();
            clear();
            mvprintw(y, x, "@");
            this->delay(0.1);
        }
    }
}

