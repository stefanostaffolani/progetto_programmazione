#include <iostream>
#include <time.h>
#include "Player.hpp"

using namespace std;
 
Player::Player(int x, int y, char avatar, Platform* p1, Bonus* b1):Item(x,y,avatar, p1, b1){
    life = 100;
    points = 0;
    mvprintw(this->y, this->x, "%c",avatar);
    //len_screen = lenS; da vedere in futuro
}

int Player::get_life(){return this->life;}

int Player::get_points(){return this->points;}

void Player::increase_points(int n){this->points += n;}

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
        //update_platform(); // ci sta
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
            }else if(mvinch(this->y + 1, this->x + versor) == 124){
                mvprintw(this->y, this->x, " ");
                this->y = HEIGHT;
                this->x = INIT_X;
                mvprintw(this->y, this->x, "%c", avatar);
                refresh();
            }else if (mvinch(this->y + 1, this->x) == 32){
                mvprintw(this->y, this->x, " ");
                this->move(ps);
            }
            //fare il caso che tocca $ (numero 36) e vedere se ne servono altri
        }else if (mvinch(this->y + 1, this->x) == 61){
            hit_something = true;
        }else{
            mvprintw(this->y, this->x, " ");
            this->y++;
            move(ps);
        }
        //update_platform();    // ci sta
        std::this_thread::sleep_for(std::chrono::milliseconds (100));
    }
}
