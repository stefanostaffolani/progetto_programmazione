#include "Item.hpp"

Item::Item(int x, int y, char avatar, Platform* p1, Bonus* b1){
    this->avatar = avatar;
    this->pos.x = x;
    this->pos.y = y;
    this->versor = 1;
    p2 = p1;
    b2 = b1;
}

void Item::move(int& ps){
    if ((versor == -1) && (this->pos.x > INIT_X)){
        mvprintw(this->pos.y, this->pos.x, " ");
        if(this->pos.x < 20 && ps >= 1){
            ps--;
            p2->printPlatforms(ps, 75, this->versor);
            b2->printCash(ps, 75, versor);
        }
        else this->pos.x--;
        mvprintw(this->pos.y, this->pos.x, "%c",avatar);
        refresh();
    }
    else if ((versor == 1) && (this->pos.x < END_X)){
        mvprintw(this->pos.y, this->pos.x, " ");
        if(this->pos.x > 55){ 
            ps++;
            p2->printPlatforms(ps, 75, this->versor);
            b2->printCash(ps, 75, versor);
        }
        else this->pos.x++;    // check for length
        mvprintw(this->pos.y, this->pos.x,"%c", avatar);
        refresh();
    }
    // p2->printPlatforms(ps, 75, this->versor);
    // b2->printCash(ps, 75, versor);
}

void Item::set_x(int n){ this->pos.x = n; }

int Item::get_x() { return this->pos.x; }

int Item::get_y() { return this->pos.y; }

int Item::get_versor(){ return this->versor;}

void Item::set_versor(int n) {this->versor = n;}
