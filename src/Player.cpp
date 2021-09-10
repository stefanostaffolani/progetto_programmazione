// #include <iostream>
// #include <time.h>
#include "Player.hpp"

using namespace std;
 
Player::Player(char avatar, Platform* p1, Bonus* b1, int x, int y):Item(avatar, p1, b1, x, y){
    life = 100;
    points = 0;
    mvprintw(this->pos.y, this->pos.x, "%c",avatar);
    //len_screen = lenS; da vedere in futuro
}

int Player::get_life(){return this->life;}

int Player::get_points(){return this->points;}

void Player::increase_points(int n){this->points += n;}

bool Player::is_hit(){
    if(mvinch(this->pos.y, this->pos.x) == 42 || mvinch(this->pos.y, this->pos.x) == 42) return true;
    else return false;
}

void Player::decrease_life(int n){this->life -= n;}

void Player::jump(int& ps, p_bullet& head){
    int i = 0;
    char c;
    bool hit_something = false;
    while((i < Y_JUMP) && !(hit_something)){
        timeout(100);
        c = getch();
        if(c == 32) head = add_bullet(head, this->pos, this->versor);
        if (mvinch(this->pos.y - 1, this->pos.x + versor) == 32){
            mvprintw(this->pos.y, this->pos.x, " ");
            this->pos.y--;
            this->move(ps);
            i++;
        } else{
            hit_something = true;
        }
        print_bullet_list(head);
        //std::this_thread::sleep_for(std::chrono::milliseconds (100));
    }
    gravity(ps, head);
}

void Player::gravity(int& ps, p_bullet& head){
    bool hit_something = false;
    //int i = 0;
    char c;
    if (mvinch(this->pos.y + 1, this->pos.x) != 32) hit_something = true;
    else hit_something = false;
    while(!(hit_something)){
        timeout(100);
        c = getch();
        if(c == 32) head = add_bullet(head, this->pos, this->versor);
        if(mvinch(this->pos.y + 1, this->pos.x + versor) != 32){
            hit_something = true;
            if (mvinch(this->pos.y + 1, this->pos.x + versor) == 36){
                mvprintw(this->pos.y, this->pos.x, " ");
                this->pos.y++;
                move(ps);
                    //increase_points(10);
                    //if (b2->findCash(ps, 75, this->x, this->y)) increase_points(10);
            }else if(mvinch(this->pos.y + 1, this->pos.x + versor) == 124){
                mvprintw(this->pos.y, this->pos.x, " ");
                this->pos.y = HEIGHT;
                this->pos.x = INIT_X;
                mvprintw(this->pos.y, this->pos.x, "%c", avatar);
                refresh();
            }else if (mvinch(this->pos.y + 1, this->pos.x) == 32){
                mvprintw(this->pos.y, this->pos.x, " ");
                this->move(ps);
            }
            //fare il caso che tocca $ (numero 36) e vedere se ne servono altri
        }else if (mvinch(this->pos.y + 1, this->pos.x) == 61){
            hit_something = true;
        }else{
            mvprintw(this->pos.y, this->pos.x, " ");
            this->pos.y++;
            move(ps);
        }
        print_bullet_list(head);
        //update_platform();    // ci sta
        //std::this_thread::sleep_for(std::chrono::milliseconds (100));
    }
}
