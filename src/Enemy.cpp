#include "Enemy.hpp"
 
Enemy::Enemy(char avatar, Platform* p1, Bonus* b1, int x, int y, int type = 0, bool on_plat = false) : Item(avatar, x, y){
    this->type = type;
    set_damage();
    p2 = p1;
    b2 = b1;
    this->on_plat = on_plat;
}

bool Enemy::check_hit(){
    return (mvinch(this->pos.y, this->pos.x + 1) == 45 || mvinch(this->pos.y, this->pos.x - 1) == 45);
}

void Enemy::set_damage(){    //TODO:togliere un tipo di nemico
    if(this->type == 0) this->damage = 10;   // nemico base
    else if(this->type == 1) this->damage = 15;  // nemico medio
    else this->damage = 20;                     // nemico forte
}

int Enemy::get_damage(){return this->get_damage();}

int Enemy::get_type(){return this->type;}

void Enemy::random_move(int ps){
    if(this->type > 0){
        int random_dir = rand()%2;     //if random_dir == 0 va a dx else a sx, se può
        mvprintw(15, 1, "%d", random_dir);
        if(random_dir) this->set_versor(-1);
        else this->set_versor(1);
        mvprintw(16, 1, "%d", this->versor);
        mvprintw(17,1,"%d", this->on_plat);
        timeout(100);
        if(this->on_plat && !this->check_plat_border(ps)){
            this->move(ps);
        }else if (!this->on_plat){
            this->move(ps);
        }
    }
}

void Enemy::random_shoot(int freq, int x_player, int ps, p_bullet& head){   // freq = 10 - difficoltà
    if(this->type > 0){
        //int x_player = player2->get_position().x;
        int dir_shoot;
        if((x_player - this->pos.x + ps) < 0) dir_shoot = -1;
        else dir_shoot = 1;
        int n = rand() % freq;
        mvprintw(20, 1, "%d", n);
        position traslated_position = {this->pos.x-ps, this->pos.y};
        if(n == 0) head = add_bullet(head, traslated_position, dir_shoot, '*');
    }
}

void Enemy::increase_damage(int inc){this->damage = this->damage + inc;}

bool Enemy::check_plat_border(int ps){ //se facendo un movimento cado dalla platform return true
    if(mvinch(this->pos.y + 1, this->pos.x + this->versor - ps) == 32) return true;
    else return false;
}
