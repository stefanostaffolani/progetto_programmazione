#include "Bullet.hpp"

Bullet::Bullet(int versor, position pos, char avatar, int damage) : Item(avatar, pos, versor){
    this->counter = RANGE;
    this->damage = damage;
    this->hit = false;
}

void Bullet::set_damage(int n){this->damage = n;}

void Bullet::increase_damage(int n){this->set_damage(this->damage+n);}  //AHAHAHAAHAH

void Bullet::decrease_counter(){this->counter--;}

int Bullet::get_counter(){return this->counter;}

int Bullet::get_damage(){return this->damage;}

void Bullet::hit_something(){
    this->hit = (mvinch(this->pos.y, this->pos.x+this->versor) != (int)' ' && mvinch(this->pos.y, this->pos.x+this->versor) != (int)avatar);
}

bool Bullet::get_hit(){return this->hit;}