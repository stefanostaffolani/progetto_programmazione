#include "Enemies.hpp"
 
Enemies::Enemies(Platform* plat, Bonus* b){
    this->difficulty = 0;
    this->fattore_incremento = 200;    // valutare poi il fattore di incremento
    this->p2 = plat;
    this->b2 = b;
    this->first = NULL;
    this->last = NULL;
    this->current = NULL;
}


void Enemies::generate(int n, int lenS, int ps){
    if(last->e->get_position().x < ps + lenS){ // se il nemico ultimo entra nellos schermo
        for(int i = 0; i < n; i++)
            addNode(n);
    }
}


void Enemies::addNode(int n){
    // genero 10 nemici
    int x;
    int y;
    bool on_plat = false;

    if(first == NULL){ // è il primo nemico che genero
        x = rand() % n + 50;
        y = this->set_y(x);
        
        on_plat = y < HEIGHT;
        int type = rand()%2;

        first = new enemies;
        current = first;
        last = first;

        first->next = NULL;
        first->prev = NULL;
        first->e = new Enemy(this->set_avatar(type),p2, b2, x, y, type, on_plat);
    }
    else{
        x = last->e->get_position().x + 50 + rand() % n; 
        y = this->set_y(x);
        
        on_plat = y < HEIGHT;
        int type = rand()%2;

        p_enem tmp = new enemies;
        tmp->next = NULL;
        tmp->prev = last;

        tmp->e = new Enemy(this->set_avatar(type),p2, b2, x, y, type, on_plat);

        last->next = tmp;
        last = tmp;
    }

}


void Enemies::removeEnemies(p_enem iter){
    if(iter == current){
        if(iter == first && iter == last){
            first = NULL;
            last = NULL;
            current = NULL;
        }
        else if(iter == first && iter != last){
            first = first->next;
            current = first;
        }
        else if(iter != first && iter == last){
            last = last->prev;
            current = last;         
        }
        else{
            iter->next->prev = iter->prev;
            iter->prev->next = iter->next;
            current = iter->prev;
        }
    }
    else if(iter == first){
        first = first->next;
        first->prev = NULL;
    }
    else if(iter == last){
        last = last->prev;
        last->next = NULL;
    }
    else{
        iter->prev->next = iter->next;
        iter->next->prev = iter->prev;
    }
    
    delete iter;
    iter = NULL;
}



void Enemies::printEnemies(int ps, int lenS, int versor, int x_player, p_bullet& head){ 

        // 1) verifica dell'aggiornamento valore current -------------------------
        if(current!=NULL){
            if(current->e->get_position().x < ps && current->next != NULL) // se sto andando avanti:
                    current = current -> next;
            else if(current -> prev != NULL && current -> prev->e->get_position().x >= ps) // se sto andando in dietro:
                    current = current -> prev;
        }

        // 2) stampare da current fino a limite schermo --------------------------
        p_enem iter = current;  

        while(iter != NULL && iter ->e->get_position().x < ps + lenS){ // cicla fino a che la nuova x di iter è fuori dallo schermo
                if(versor == 1) iter->e->delete_item(ps-1); // premo d 
                else if(versor == -1) iter->e->delete_item(ps+1); // premo a
                if(iter ->e->get_position().x >= ps && iter ->e->get_position().x < ps + lenS - 1){
                    iter->e->print_item(ps);
                }                
                iter = iter->next;
        }

} 


int Enemies::find_enemy(int ps, int lenS, int plx, int ply){
    // 1) verifica che il bonus sia stato trovato, 
    // 2) ritorna il tipo di bonus che ha trovato
    // plx ply -> player position x, player position y

    p_enem iter = current;
    int enemy_type_found = -1;

    while(iter != NULL && iter->e->get_position().x < ps+lenS){
        
        if(iter->e->get_position().x == plx + ps && iter->e->get_position().y == ply){

            enemy_type_found = iter->e->get_type();
            
            //TODO: da verificare stammerda sotto 
            iter->e->delete_item(plx);
            iter->e->delete_item(plx+1);
            refresh();
            
            return enemy_type_found;
        }
        iter = iter->next;
    }
    return enemy_type_found;

}



void Enemies::move_and_shoot(int lenS, int ps, int x_player, p_bullet& head){
    p_enem iter = this->current;
    if(iter != NULL){
        while(iter->next != NULL && iter->e->get_position().x < lenS + ps){
            if(iter->e->get_type()){
                //iter->e->delete_item();
                if(iter->e->get_versor() == 1) mvprintw(iter->e->get_position().y, iter->e->get_position().x - ps + 1, " "); // premo d 
                else if(iter->e->get_versor() == -1) mvprintw(iter->e->get_position().y, iter->e->get_position().x - ps - 1, " "); // premo a
                iter->e->random_move(ps);
                iter->e->random_shoot((10-this->difficulty), x_player, ps, head);
            }
            iter = iter->next;
        }
    }
}


void Enemies::increase_difficulty(int ps){    // operazione per aumentare la difficoltà dei nemici lungo il gioco (da valutare)
    if(this->difficulty < 9 && (this->difficulty < (this->difficulty + (ps / this->fattore_incremento)))){
        this->difficulty = this->difficulty + (ps / this->fattore_incremento);
    }
}



//per la frequenza di sparo si potrebbe fare (10 - difficult) (10 livelli di difficoltà), al decimo livello spara sempre
int Enemies::set_y(int x){   // non so se sia necessaria la x come argomento
    bool found_plat = false;

    p_node iter = p2->get_current();
    if(iter == NULL) return HEIGHT;
    else if(iter->prev == NULL) return HEIGHT;
    else{
        while(iter->next != NULL && iter->x < x)
            iter = iter->next;
        if(iter->prev->x + iter->prev->len - 1 < x)    // -1 perchè x + len sborda di 1
            return HEIGHT;
        else{
            if(rand()%2)return iter->prev->y - 1;
            else return HEIGHT;
        }
    }
}

char Enemies::set_avatar(int type){
    if(type == 0) return 'o';
    else return 'O';
} 
