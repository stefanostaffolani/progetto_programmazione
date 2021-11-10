#include "Enemy.hpp"
 
Enemy::Enemy(char avatar, Platform* p1, position pos, int type = 0, bool on_plat = false):Item(avatar, pos, 0){
    this->type = type;
    set_damage();
    p2 = p1;
    this->on_plat = on_plat;
    if(type == 0) life = 20;
    else life = 50;
}

void Enemy::decrease_life(int n){this->life -= n;}

int Enemy::get_life(){return this->life;}

void Enemy::set_damage(){ 
    if(this->type == 0) this->damage = 10;   // nemico base
    else this->damage = 20;                     // nemico forte
}

int Enemy::get_damage(){return this->damage;}

int Enemy::get_type(){return this->type;}

void Enemy::random_move(int ps){  //TODO: controllare questa funzione sulle platform
    if(this->type > 0){
        mvprintw(22,1,"%d,%d",pos.x,pos.y);
        int random_dir = rand()%2;     //if random_dir == 0 va a dx else a sx, se può
        if(random_dir) this->set_versor(-1);
        else this->set_versor(1);
        if(mvinch(this->pos.y, this->pos.x + this->versor - ps) == (int)' '){
            timeout(100);
            mvprintw(21, 20, "è sulla plat:%d",on_plat);
            if(this->on_plat && !this->check_plat_border(ps)){
                mvprintw(21,1,"ok si muove");
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
        if((x_player - this->pos.x + ps) < 0) dir_shoot = -1;
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
