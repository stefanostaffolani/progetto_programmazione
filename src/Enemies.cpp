#include "Enemies.hpp"
 
Enemies::Enemies(Platform* plat, Bonus* b){       // skeleton, solo alcune possibili funzioni per Enemies
    this->difficulty = 0;
    this->fattore_incremento = 200;    // valutare poi il fattore di incremento
    this->p2 = plat;
    this->b2 = b;
}

void Enemies::increase_difficulty(int ps){    // operazione per aumentare la difficoltà dei nemici lungo il gioco (da valutare)
    if(this->difficulty < 9 && (this->difficulty < (this->difficulty + (ps / this->fattore_incremento)))){
        this->difficulty = this->difficulty + (ps / this->fattore_incremento);
    }
}

void Enemies::printEnemies(int ps, int lenS, int versor){ // ========================

        // 1) verifica dell'aggiornamento valore current -------------------------
                // se sto andando avanti:
        if(current!=NULL){
            if(current->e->get_position().x < ps && current->next != NULL)
                    current = current -> next;
                    // se sto andando in dietro:
            else if(current -> prev != NULL && current -> prev->e->get_position().x >= ps)
                    current = current -> prev;
        }

        // 2) stampare da current fino a limite schermo --------------------------
        p_enem iter = current;  

        while(iter != NULL && iter ->e->get_position().x < ps + lenS){ // cicla fino a che la nuova x di iter è fuori dallo schermo
                if(versor == 1) mvprintw(iter->e->get_position().y, iter->e->get_position().x - ps + 1, " "); // premo d 
                else if(versor == -1) mvprintw(iter->e->get_position().y, iter->e->get_position().x - ps - 1, " "); // premo a
                if(iter ->e->get_position().x >= ps && iter ->e->get_position().x < ps + lenS - 1){
                    if(iter->e->get_type() == 0)
                        mvprintw(iter ->e->get_position().y, iter ->e->get_position().x - ps, "o");
                    else if(iter->e->get_type() == 1)
                        mvprintw(iter ->e->get_position().y, iter->e->get_position().x - ps, "O");
                }                
                iter = iter->next;
        }

} // fine funzione printEnemies() ==================================================

char Enemies::set_avatar(int type){
    if(type == 0) return 'o';
    else return 'O';
}

void Enemies::generate(int n){
    // genero 10 nemici
    int i;
    for(i = 1; i <= 10; i++){
        int x = rand() % n + (50 * i);
        int y = this->set_y(x);
        bool on_plat = false;
        if(y < HEIGHT) on_plat = true;
        int type = rand()%2;

        if(first == NULL){ // è il primo nemico che piazzo 
            first = new enemies;
            current = first;
            last = first;

            first->next = NULL;
            first->prev = NULL;
            first->e = new Enemy(this->set_avatar(type),p2, b2, x, y, type, on_plat);
        }
        else{
            p_enem tmp = new enemies;
            tmp->next = NULL;
            tmp->prev = last;

            tmp->e = new Enemy(this->set_avatar(type),p2, b2, x, y, type, on_plat);

            last->next = tmp;
            last = tmp;
        }
    }


}




//per la frequenza di sparo si potrebbe fare (10 - difficult) (10 livelli di difficoltà), al decimo livello spara sempre

//TODO:rifare questa funzione per lavorare con la lista
int Enemies::set_y(int x){   // non so se sia necessaria la x come argomento
    int i = 0;
    bool found_plat = false;

    p_node iter = p2->get_current();
    while(iter->x < x)
        iter = iter->next;
    if(iter->prev->x + iter->prev->len < x)    //TODO:capire perchè con -1 funziona
        return HEIGHT;
    else{
        if(rand()%2)return iter->prev->y - 1;
        else return HEIGHT;
    }
    // while ((i < HEIGHT) && !(found_plat)){
    //     if(mvinch(i,x) == 61) found_plat = true;
    //     else i++;
    // }
    // if (found_plat && rand() % 2)
    //     return i;
    // return HEIGHT;
}