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

// void Enemy::generate_on_platform(int x){   // non so se sia necessaria la x come argomento
//     int i = 0;
//     bool found_plat = false;
//     while ((i < HEIGHT) && !(found_plat)){
//         if(mvinch(i,x) == 61) found_plat = true;
//         else i++;
//     }
//     if (found_plat){
//         if(rand() % 2) this->on_plat = true;
//         else this->on_plat = false;
//     }
//     this->pos.y = i;
// }

bool Enemy::check_plat_border(){ //se facendo un movimento cado dalla platform return true
    if(mvinch(this->pos.y, this->pos.x + this->versor) == 32) return true;
    else return false;
}

// Enemy::generate(){
//     // guarda il valore di ps e stabilisce il livello, all'inizio ci sono più Enemy
//     // scarsi, più vai avanti più te ne trovi di forti

//     if(ps < 1000) 
//         lvl = 0;
//     else if(ps >= 1000 && ps < 2000){
//     if(rand()%2 == 0) 
//         lvl = 0; 
//     else 
//         lvl = 1; 
//     }
// }


/*


*/
