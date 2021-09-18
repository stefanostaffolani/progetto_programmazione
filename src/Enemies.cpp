#include "Enemies.hpp"

Enemies::Enemies(){       // skeleton, solo alcune possibili funzioni per Enemies
    this->difficult = 0;
    this->fattore_incremento = 10;
}

void Enemies::increase_difficult(int ps){    // operazione per aumentare la difficoltà dei nemici lungo il gioco (da valutare)
    this->difficult = this->difficult + (ps / this->fattore_incremento);
}

//TODO:rifare questa funzione per lavorare con la lista
// void Enemies::generate_on_platform(int x){   // non so se sia necessaria la x come argomento
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