#include "Enemies.hpp"
 
Enemies::Enemies(){       // skeleton, solo alcune possibili funzioni per Enemies
    this->difficulty = 0;
    this->fattore_incremento = 10;    // valutare poi il fattore di incremento
}

void Enemies::increase_difficulty(int ps){    // operazione per aumentare la difficoltà dei nemici lungo il gioco (da valutare)
    if(this->difficulty < 9){
        this->difficulty = this->difficulty + (ps / this->fattore_incremento);
    }
}

<<<<<<< HEAD

void Enemies::generate(){
    // 



}




//per la frequenza di sparo si potrebbe fare (10 - difficult) (10 livelli di difficoltà), al decimo livello spara sempre
=======
//per la frequenza di sparo si potrebbe fare (10 - difficulty) (10 livelli di difficoltà), al decimo livello spara sempre
>>>>>>> 613e192f4b979c0576f9b8917ee194de22519606

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