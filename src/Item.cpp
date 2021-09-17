#include "Item.hpp"

Item::Item(char avatar, int x = 3, int y = 12){
    this->avatar = avatar;
    this->pos.x = x;
    this->pos.y = y;
    this->versor = 1;
}

void Item::move(){
    if ((versor == -1) && (this->pos.x > INIT_X)){
        this->delete_item();
        this->pos.x--;
        this->print_item();
    }else if ((versor == 1) && (this->pos.x < END_X)){
        this->delete_item();
        this->pos.x++;
        this->print_item();
    }
    refresh();
}

void Item::print_item(){mvprintw(this->pos.y, this->pos.x, "%c", this->avatar);}

void Item::delete_item(){mvprintw(this->pos.y, this->pos.x, " ");}

void Item::set_x(int n){ this->pos.x = n; }

position Item::get_position(){ return this->pos;}

int Item::get_versor(){ return this->versor;}

void Item::set_versor(int n) {this->versor = n;}