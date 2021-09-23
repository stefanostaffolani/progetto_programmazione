#include "Enemies.hpp"
 
Enemies::Enemies(){       // skeleton, solo alcune possibili funzioni per Enemies
    this->difficulty = 0;
    this->fattore_incremento = 200;    // valutare poi il fattore di incremento
}

void Enemies::increase_difficulty(int ps){    // operazione per aumentare la difficoltà dei nemici lungo il gioco (da valutare)
    if(this->difficulty < 9 && (this->difficulty < (this->difficulty + (ps / this->fattore_incremento)))){
        this->difficulty = this->difficulty + (ps / this->fattore_incremento);
    }
}

<<<<<<< HEAD
void Enemies::printEnemies(int ps, int lenS, int versor){ // ========================
=======
>>>>>>> 2782e3e9365b1a70d62ef9c19e343bed4212a20f

        // 1) verifica dell'aggiornamento valore current -------------------------
                // se sto andando avanti:
        if(current!=NULL){
            if(current -> x < ps && current->next != NULL)
                    current = current -> next;
                    // se sto andando in dietro:
            else if(current -> prev != NULL && current -> prev -> x >= ps)
                    current = current -> prev;
        }

        // 2) stampare da current fino a limite schermo --------------------------
        p_enem iter = current;  

        while(iter != NULL && iter -> x < ps + lenS){ // cicla fino a che la nuova x di iter è fuori dallo schermo
                if(versor == 1) mvprintw(iter->y, iter->x - ps + 1, " "); // premo d 
                else if(versor == -1) mvprintw(iter->y, iter->x - ps - 1, " "); // premo a
                if(iter -> x >= ps && iter -> x < ps + lenS - 1){
                    if(iter->type == 0)
                        mvprintw(iter -> y, iter -> x - ps, "$");
                    else if(iter->type == 1)
                        mvprintw(iter -> y, iter -> x - ps, "V");
                }                
                iter = iter->next;
        }

} // fine funzione printEnemies() ==================================================



void Enemies::generate(){
    // genero 10 nemici
    int i;
    for(i = 1; i <= 10; i++){
        Enemy* e = new Enemy();
        
    {


}




//per la frequenza di sparo si potrebbe fare (10 - difficult) (10 livelli di difficoltà), al decimo livello spara sempre

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