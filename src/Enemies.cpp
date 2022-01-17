#include "Enemies.hpp"
 
Enemies::Enemies(Platform* plat){
    this->difficulty = 0;
    this->fattore_incremento = FACTOR;    // valutare poi il fattore di incremento
    this->p2 = plat;
    this->first = NULL;
    this->last = NULL;
    this->current = NULL;
} 

// se l'ultimo nemico che è stato generato entra nello schermo
// chiama per n volte la funzione addNode che aggiunge un nuovo nemico 
void Enemies::generate(int n, int ps){
    if(first == NULL) addNode(5);
    if(last->e->get_position().x < ps + LENGTH){ // se il nemico ultimo entra nello schermo
        for(int i = 0; i < n; i++)
            addNode(n);
    }
}

// aggiungie un nemico nella lista di nemici
void Enemies::addNode(int n){
    int x;
    int y;
    bool on_plat = false;

    if(first == NULL){ // è il primo nemico che genero
        x = rand() % n + ENEM_x_POS;
        y = this->set_y(x);
        
        on_plat = y < HEIGHT;
        int type = rand()%2;

        first = new enemies;
        current = first;
        last = first;

        first->next = NULL;
        first->prev = NULL;
        position pos_enemy = {x,y};
        first->e = new Enemy(this->set_avatar(type),p2, pos_enemy, type, on_plat, P_DAMAGE+2*this->difficulty*type);
    }
    else{
        x = last->e->get_position().x + ENEM_x_POS + rand() % n; 
        y = this->set_y(x);
        
        on_plat = y < HEIGHT;
        int type = rand()%2;

        p_enem tmp = new enemies;
        tmp->next = NULL;
        tmp->prev = last;
        position pos_enemy = {x,y};
        tmp->e = new Enemy(this->set_avatar(type),p2, pos_enemy, type, on_plat, P_DAMAGE+2*this->difficulty*type);

        last->next = tmp;
        last = tmp;
    }

}

// rimuove un nemico dalla lista dei nemici
void Enemies::removeEnemies(p_enem& iter){

    if(iter == current){
        if(iter == first && iter == last){
            first = NULL;
            last = NULL;
            current = NULL;
        }
        else if(iter == first && iter != last){
            first = first->next;
            current = first;
            first->prev = NULL;
        }
        else if(iter != first && iter == last){
            last = last->prev;
            current = last;    
            last->next = NULL;     
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

// aggiorna il valore del puntatore current, viene chiamata prima della stampa
void Enemies::update_current(int ps, int versor){
    if(current!=NULL){
        if(current->e->get_position().x < ps && current->next != NULL) // se sto andando avanti:
            current = current -> next;
        else if(current -> prev != NULL && current -> prev->e->get_position().x >= ps) // se sto andando in dietro:
            current = current -> prev;
    }
}

void Enemies::printEnemies(int ps, int versor){ 

        // 1) verifica dell'aggiornamento valore current -------------------------
        update_current(ps, versor);

        // 2) stampare da current fino a limite schermo --------------------------
        p_enem iter = current;  
        if(iter != NULL){
            while(iter->next != NULL && iter ->e->get_position().x < ps + LENGTH){ // cicla fino a che la nuova x di iter è fuori dallo schermo
                    if(versor == 1) iter->e->delete_item(ps-1); // premo d, vado a dx ==> avevo incrementato ps
                    else if(versor == -1) iter->e->delete_item(ps+1); // premo a, vado a sx ==> avevo decrementato ps
                    if(iter ->e->get_position().x >= ps && iter ->e->get_position().x < ps + LENGTH - 1){
                        iter->e->print_item(ps);
                    }                
                    iter = iter->next;
            }
        }

} 

void Enemies::move_and_shoot(int ps, int x_player, Shoot* s2){     //scorre la lista dei nemici e li fa muovere e sparare
    p_enem iter = this->current;
    if(iter != NULL){
        while(iter->next != NULL && iter->e->get_position().x < LENGTH + ps){
            if(iter->e->get_type()){   // se il nemico non e' base
                if(iter->e->get_versor() == 1) mvprintw(iter->e->get_position().y, iter->e->get_position().x - ps + 1, " "); // premo d, quindi vado a dx  ==> avevo incremento ps
                else if(iter->e->get_versor() == -1) mvprintw(iter->e->get_position().y, iter->e->get_position().x - ps - 1, " "); // premo a, quindi vado a sx ==> avevo decrementato ps
                iter->e->random_move(ps);
                iter->e->random_shoot((12-this->difficulty), x_player, ps, s2);   // 12 - diff ==> probabilita' di sparo fino a 50%
            }
            iter = iter->next;
        }
    }
}

int Enemies::get_difficulty(){return difficulty;}

void Enemies::increase_difficulty(int ps){    // operazione per aumentare la difficoltà dei nemici lungo il gioco (da valutare)
    if(this->difficulty < 10) this->difficulty = ps / this->fattore_incremento;
}

int Enemies::set_y(int x){    
    bool found_plat = false;

    p_node iter = p2->get_current();
    if(iter == NULL) return HEIGHT;
    else if(iter->prev == NULL) return HEIGHT;
    else{
        while(iter->next != NULL && iter->x < x)  // arriva fino alla piattaforma dopo x
            iter = iter->next;
        if(iter->prev->x + iter->prev->len - 1 < x)    // -1 perchè x + len sborda di 1
            return HEIGHT;
        else{
            if(rand()%2)return iter->prev->y - 1;    //50% possibilita' su plat 50% possibilita' su terra
            else return HEIGHT;
        }
    }
}

char Enemies::set_avatar(int type){
    if(type == 0) return 'o';
    else return 'O';
} 

void Enemies::delete_base_enemy(position player_pos, int ps){
    p_enem iter = this->current;
    bool found = false;
    int x_enem,y_enem;
    
    while(iter != NULL && !found){
        x_enem = iter->e->get_position().x - ps;
        y_enem = iter->e->get_position().y;
        if((x_enem == player_pos.x) && (y_enem == player_pos.y) && (iter->e->get_type()==0)){   //se e' il nemico in posizione richiesta cancella
            found = true;
            this->removeEnemies(iter);
        }else {
            iter = iter->next;
        }
    }
}

void Enemies::check_is_hit(int ps, Shoot* s){
    p_enem iter = this->current;
    bool end_of_screen = false;
    bool stop;
    p_bullet iter_b;
    while(iter != NULL && !end_of_screen){
        if(iter->e->get_position().x < (ps + LENGTH)){
            iter_b = s->get_head();
            stop = false;
            while(iter_b != NULL && !stop){
                if(iter->e->get_position().x - ps == iter_b->b->get_position().x \
                && iter->e->get_position().y == iter_b->b->get_position().y && \
                (iter_b->b->get_avatar() != '*')){  //TODO:in caso poi fare utils
                    
                    iter->e->decrease_life(iter_b->b->get_damage());
                    if(iter->e->get_life() <= 0) this->removeEnemies(iter);
                    stop = true;
                }else
                 iter_b = iter_b->next;
            }
        if(iter != NULL)
            iter = iter->next;
        }else end_of_screen = true;
    }
}
