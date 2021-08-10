#include "Item.hpp"

Item::Item(int x, int y, char avatar, Platform* p1, Bonus* b1){
    this->avatar = avatar;
    this->x = x;
    this->y = y;
    this->versor = 1;
    p2 = p1;
    b2 = b1;
}

void Item::move(int& ps){
    if ((versor == -1) && (this->x > INIT_X)){
        mvprintw(this->y, this->x, " ");
        if(this->x < 20 && ps >= 1){
            ps--;
            p2->printPlatforms(ps, 75, this->versor);
            b2->printCash(ps, 75, versor);
        }
        else this->x--;
        mvprintw(this->y, this->x, "%c",avatar);
        refresh();
    }
    else if ((versor == 1) && (this->x < END_X)){
        mvprintw(this->y, this->x, " ");
        if(this->x > 55){ 
            ps++;
            p2->printPlatforms(ps, 75, this->versor);
            b2->printCash(ps, 75, versor);
        }
        else this->x++;    // check for length
        mvprintw(this->y, this->x,"%c", avatar);
        refresh();
    }
    // p2->printPlatforms(ps, 75, this->versor);
    // b2->printCash(ps, 75, versor);
}

void Item::set_x(int n){ this->x = n; }

int Item::get_x() { return this->x; }

int Item::get_y() { return this->y; }

int Item::get_versor(){ return this->versor;}

void Item::set_versor(int n) {this->versor = n;}
