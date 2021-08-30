#include "Enemy.hpp"

Enemy::Enemy(char avatar, Platform* p1, Bonus* b1, int x, int y) : Item(avatar, p1, b1, x, y){
    generate();
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