#include "Enemy.hpp"
 
Enemy::Enemy(char avatar, Platform* p1, position pos, int type = 0, bool on_plat = false):Item(avatar, pos, 0){
    this->type = type;
    set_damage();
    p2 = p1;
    this->on_plat = on_plat;
    if(type == 0) life = BASE_ENEMY_LIFE;    // setto la vita in base al tipo
    else life = HARD_ENEMY_LIFE;
}

void Enemy::decrease_life(int n){this->life -= n;}

int Enemy::get_life(){return this->life;}

void Enemy::set_damage(){ 
    if(this->type == 0) this->damage = P_DAMAGE;   // nemico base
    else this->damage = 2*P_DAMAGE;                     // nemico forte
}

int Enemy::get_damage(){return this->damage;}

int Enemy::get_type(){return this->type;}

void Enemy::random_move(int ps){
    if(this->type > 0){
        int random_dir = rand()%2;     //if random_dir == 0 va a dx else a sx, se può
        if(random_dir) this->set_versor(-1);
        else this->set_versor(1);
        if(mvinch(this->pos.y, this->pos.x + this->versor - ps) == (int)' '){    // si sposta se non ha nulla di fianco
            timeout(100);                   // si sposta una volta ogni ciclo di gioco
            if(this->on_plat && !this->check_plat_border(ps)){
                this->move(ps);
            }else if (!this->on_plat){
                this->move(ps);
            }
        }
    }
}

void Enemy::random_shoot(int freq, int x_player, int ps, Shoot* s2){   // freq = 10 - difficoltà
    if(this->type > 0){         //sparano solo i nemici forti
        int dir_shoot;
        if((x_player - this->pos.x + ps) < 0) dir_shoot = -1;   // la direzione di sparo e' verso il player]
        else dir_shoot = 1;
        int n = rand() % freq;      // se aumenta la frequenza aumenta la probabilità di sparare
        position traslated_position = {this->pos.x-ps, this->pos.y};
        if(n == 0) s2->add_bullet(traslated_position, dir_shoot, '*', this->damage);     //condizione per sparare
    }
}

void Enemy::increase_damage(int inc){this->damage = this->damage + inc;}

bool Enemy::check_plat_border(int ps){ //se facendo un movimento cado dalla platform return true
    if(mvinch(this->pos.y + 1, this->pos.x + this->versor - ps) == (int)' ') return true;
    else return false;
}
