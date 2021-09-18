#include "Enemy.hpp"

Enemy::Enemy(char avatar, Platform* p1, Bonus* b1, int x, int y, int type = 0) : Item(avatar, x, y){
    this->type = type;
    set_damage();
    p2 = p1;
    b2 = b1;
}

void Enemy::set_damage(){
    if(this->type == 0) this->damage = 10;   // nemico base
    else if(this->type == 1) this->damage = 15;  // nemico medio
    else this->damage = 20;                     // nemico forte
}

int Enemy::get_damage(){return this->get_damage();}

void Enemy::random_move(){
    if(this->type > 0){
        int random_dir = rand()%2;     //if random_dir == 0 va a dx else a sx, se può
        if(random_dir) this->set_versor(-1);
        else this->set_versor(1);
        if(this->on_plat && !this->check_plat_border()){
            this->move();
        }else if (!this->on_plat){
            this->move();
        }
    }
}

void Enemy::random_shoot(int freq, p_bullet head){   //su enemies pensare a come settare la frequenza
    if(this->type > 0){
        int n = rand() % freq;
        if(n == 0) add_bullet(head, this->pos, this->versor, '*');
    }
}

void Enemy::increase_damage(int inc){this->damage = this->damage + inc;}

bool Enemy::check_plat_border(){ //se facendo un movimento cado dalla platform return true
    if(mvinch(this->pos.y, this->pos.x + this->versor) == 32) return true;
    else return false;
}
