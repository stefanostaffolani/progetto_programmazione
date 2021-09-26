// #include <iostream>
// #include <time.h>
#include "Player.hpp"

using namespace std;

#define SPACE 32
#define EQUAL 61
#define DOLLAR 36
#define PIPE 124

Player::Player(char avatar, Platform* p1, Bonus* b1, Enemies* e1, int x, int y):Item(avatar, x, y){
    life = 100;
    points = 0;
    mvprintw(this->pos.y, this->pos.x, "%c",avatar);
    p2 = p1;
    b2 = b1;
    e2 = e1;
    //len_screen = lenS; da vedere in futuro
}

int Player::get_life(){return this->life;}

int Player::get_points(){return this->points;}

void Player::increase_points(int n){this->points += n;}

bool Player::is_hit(){
    return (mvinch(this->pos.y, this->pos.x + 1) == 42 || mvinch(this->pos.y, this->pos.x - 1) == 42);
}

void Player::move(int& ps){
    if((this->versor == -1) && (this->pos.x < 20) && (ps >= 1)){
        ps--;
    }else if ((this->versor == 1) && (this->pos.x > 55)){
        ps++;
    }
    else Item::move();
    this->print_item();
    p2->printPlatforms(ps, 75, this->versor);
    b2->print_bonus(ps, 75, this->versor);
    e2->printEnemies(ps, 75, this->versor);
}

void Player::decrease_life(int n){this->life -= n;}
void Player::increase_life(int n){this->life += n;}
void Player::set_life(int n) {this->life = n;}

void Player::jump(int& ps, p_bullet& head){
    int i = 0;
    char c;
    bool hit_something = false;
    position diagonale, sopra;
    while((i < Y_JUMP) && !(hit_something)){
        timeout(100);
        c = getch();
        diagonale = {this->pos.x+this->versor, this->pos.y - 1};
        sopra = {this->pos.x, this->pos.y - 1};
        if(c == 32) head = add_bullet(head, this->pos, this->versor, '-');
        if (mvinch(diagonale.y, diagonale.x) == 32){
            this->delete_item();
            if(mvinch(sopra.y, sopra.x) == 32){
                //mvprintw(this->pos.y, this->pos.x, " ");
                this->pos.y--;
                this->move(ps);
                //this->print_item();
            }else{
                this->delete_item();
                this->pos.y--;
                this->pos.x += this->versor;
                this->print_item();
            }
            i++;
        } else{
            hit_something = true;
        }
        print_bullet_list(head);
    }
    gravity(ps, head);
}

void Player::gravity(int& ps, p_bullet& head){
    bool hit_something = false;
    //int i = 0;
    char c;
    if (mvinch(this->pos.y + 1, this->pos.x) != SPACE && mvinch(this->pos.y + 1, this->pos.x) != DOLLAR && mvinch(this->pos.y + 1, this->pos.x) != 86) hit_something = true;
    else hit_something = false;
    position diagonale, sotto, laterale;
    while(!(hit_something)){
        timeout(100);
        
        //per sparare
        c = getch();
        if(c == SPACE) head = add_bullet(head, this->pos, this->versor, '-');
        
        diagonale = {this->pos.x + versor, this->pos.y + 1};
        sotto = {this->pos.x, this->pos.y+1};
        laterale = {this->pos.x+this->versor, this->pos.y};
        if (mvinch(sotto.y, sotto.x) == EQUAL || mvinch(sotto.y, sotto.x) == 45){   // ho qualcosa sotto
            hit_something = true;
        }
        else if(mvinch(diagonale.y, diagonale.x) != SPACE){
            hit_something = true;
            if (mvinch(diagonale.y, diagonale.x) == DOLLAR || mvinch(diagonale.y, diagonale.x) == 86){
                this->delete_item();
                //mvprintw(this->pos.y, this->pos.x, " ");
                this->pos.y++;
                this->move(ps);
                //increase_points(10);
                //if (b2->findCash(ps, 75, this->x, this->y)) increase_points(10);
            }else if(mvinch(diagonale.y, diagonale.x) == PIPE){
                this->delete_item();
                //mvprintw(this->pos.y, this->pos.x, " ");
                this->pos.y = HEIGHT;
                this->pos.x = INIT_X;
                this->print_item();
                //mvprintw(this->pos.y, this->pos.x, "%c", avatar);
                refresh();
            }else if (mvinch(sotto.y, sotto.x) == SPACE){
                this->delete_item();
                //mvprintw(this->pos.y, this->pos.x, " ");
                this->move(ps);
            }
            //vedere se ne servono altri
        }
        else{
            if(mvinch(laterale.y, laterale.x) == EQUAL || mvinch(laterale.y, laterale.x) == 111 || mvinch(laterale.y, laterale.x) == 79){   // perchè potrebbe cancellare lo spigolo della platform
                this->delete_item();
                this->pos.x+=versor;
                this->pos.y++;
                this->print_item();
            }
            else{
                this->move(ps);
                this->delete_item();
                //mvprintw(this->pos.y, this->pos.x, " ");
                this->pos.y++;
                this->print_item();
            }
    }
        print_bullet_list(head);
    }
}