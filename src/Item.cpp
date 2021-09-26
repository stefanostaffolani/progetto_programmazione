#include "Item.hpp"

Item::Item(char avatar, int x = 3, int y = 12){
    this->avatar = avatar;
    this->pos.x = x;
    this->pos.y = y;
    this->versor = 1;
}

void Item::move(int ps){
    if ((versor == -1) && ((this->pos.x - ps) > INIT_X)){
        this->delete_item(ps);
        this->pos.x--;
        this->print_item(ps);
    }else if ((versor == 1) && ((this->pos.x - ps) < END_X)){
        this->delete_item(ps);
        this->pos.x++;
        this->print_item(ps);
    }
    refresh();
}

void Item::print_item(int ps){mvprintw(this->pos.y, this->pos.x - ps, "%c", this->avatar);}

void Item::delete_item(int ps){mvprintw(this->pos.y, this->pos.x - ps, " ");}

void Item::set_x(int n){ this->pos.x = n; }

position Item::get_position(){ return this->pos;}

int Item::get_versor(){ return this->versor;}

void Item::set_versor(int n) {this->versor = n;}