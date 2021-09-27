#include "Bonus.hpp"
#include "time.h"

Bonus::Bonus(Platform* p){
    srand(time(NULL));
    this->first = NULL;
    this->last = NULL;
    this->current = NULL;
    this->p = p;
}

void Bonus::generate(int n, int lenS, int ps){
    if(last->x < ps + lenS){
        for(int i = 0; i < n; i++)
            addNode(n);
    }
}

void Bonus::addNode(int n){

    if(first == NULL){ // è il primo bonus che genero
        first = new bonuslist();
        current = first;
        last = first;

        first->next = NULL;
        first->prev = NULL;
        first->x = rand() % n + 30;
        first->y = this->set_y(first->x);
        first->type = (rand()%10 == 0) ? 1 : 0;
    }
    else{
        p_bon tmp = new bonuslist();
        tmp->next = NULL;
        tmp->prev = last;
        tmp->x = last->x + 50  + rand() % n;
        tmp->y = this->set_y(first->x);

        last->next = NULL;
        last = tmp;
    }

}

void Bonus::removeBonus(p_bon iter){
    // verifico se il bonus è current, last, first altirmenti nulla
    if(iter == current){ 
        if(iter != first)
            current = iter->prev;
        else if(iter != last)
            current = iter -> next;
        else {
            current = NULL;
            last = NULL;
            first = NULL;
        }
    }
    if(iter == last){
        last = last->prev;
        last->next = NULL;
    }
    else if(iter == first){
        first = first->next;
        first->prev = NULL;
    }
    else{
        iter->prev->next = iter->next;
        iter->next->prev = iter->prev;
    }
    delete iter;
    iter = NULL;
}


void Bonus::print_bonus(int ps, int lenS, int versor){

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
        p_bon iter = current;  

        if(current != NULL){
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
        }
}

int Bonus::find_bonus(int ps, int lenS, int plx, int ply){
    
    // 1) verifica che il bonus sia stato trovato, 
    // 2) ritorna il tipo di bonus che ha trovato
    // 3) cancella dalla lista l'elemento
    // plx ply -> player position x, player position y
    
    p_bon iter = current;
    int bonus_type_found = -1;

    while(iter != NULL && iter->x < ps+lenS){
        
        if(iter->x == plx + ps && iter->y == ply) {

            bonus_type_found = iter->type;
            removeBonus(iter);

            mvprintw(ply, plx, "@");
            mvprintw(ply, plx + 1, " ");
            refresh();

            return bonus_type_found;
        }
        iter = iter->next;
    }
    return bonus_type_found;
}


int Bonus::set_y(int x){
    p_node iter = p->get_current();
    if (iter == NULL) return 12;
    while(iter->next != NULL && iter->x < x)
        iter = iter->next;
    if(iter->prev->x + iter->prev->len - 1 < x)    // -1 perchè x + len sborda di 1
        return 12;
    else{
        if(rand()%2)return iter->prev->y - 1;
        else return 12;
    }
}