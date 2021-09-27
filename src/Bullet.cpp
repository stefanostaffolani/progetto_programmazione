#include "Bullet.hpp"

Bullet::Bullet(int versor, position pos, char avatar, int damage) : Item(avatar, pos, versor){
    this->counter = RANGE;
    this->damage = damage;
}

void Bullet::set_damage(int n){this->damage = n;}

void Bullet::increase_damage(int n){this->set_damage(this->damage+n);}  //AHAHAHAAHAH

void Bullet::decrease_counter(){this->counter--;}

int Bullet::get_counter(){return this->counter;}

bool Bullet::hit_something(){
    return (mvinch(this->pos.y, this->pos.x+this->versor) != (int)' ' || mvinch(this->pos.y, this->pos.x+this->versor) != (int)avatar);
} 