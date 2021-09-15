#include "Item.hpp"

Item::Item(char avatar, Platform* p1, Bonus* b1,int x = 3, int y = 12){
    this->avatar = avatar;
    this->pos.x = x;
    this->pos.y = y;
    this->versor = 1;
    p2 = p1;
    b2 = b1;
}

void Item::move(int& ps){
    if ((versor == -1) && (this->pos.x > INIT_X)){
        this->delete_item();
        //mvprintw(this->pos.y, this->pos.x, " ");
        if(this->pos.x < 20 && ps >= 1){
            ps--;
            p2->printPlatforms(ps, 75, this->versor);
            b2->printCash(ps, 75, versor);
        }
        else this->pos.x--;
        this->print_item();
        //mvprintw(this->pos.y, this->pos.x, "%c",avatar);
        refresh();
    }
    else if ((versor == 1) && (this->pos.x < END_X)){
        this->delete_item();
        //mvprintw(this->pos.y, this->pos.x, " ");
        if(this->pos.x > 55){ 
            ps++;
            p2->printPlatforms(ps, 75, this->versor);
            b2->printCash(ps, 75, versor);
        }
        else this->pos.x++;    // check for length
        this->print_item();
        //mvprintw(this->pos.y, this->pos.x,"%c", avatar);
        refresh();
    }
}

void Item::print_item(){mvprintw(this->pos.y, this->pos.x, "%c", this->avatar);}

void Item::delete_item(){mvprintw(this->pos.y, this->pos.x, " ");}

void Item::set_x(int n){ this->pos.x = n; }

position Item::get_position(){ return this->pos;}

int Item::get_versor(){ return this->versor;}

void Item::set_versor(int n) {this->versor = n;}