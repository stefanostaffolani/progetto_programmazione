#include <iostream>
#include <ncurses.h>
#include <time.h>
#include <string.h>
#include "Platform.hpp"
#include "Bonus.hpp"
 
using namespace std;

Bonus::Bonus(){
    first = new bonuslist();
    first->y = -10;
    first->x = -10;
    first->prev = NULL;
    first->next = NULL;
    last = first;
    current = first;
}

void Bonus::add_bonus(p_node p, int h){
    
    // p_node puntatore a platform
    // questo ciclo scorre avatìnti di 6 platform 
    // per essere sicuro di aggiungere il nuovo bonus
    // al di fuori dello schermo
    for(int i = 0; i < 6; i++){
        if(p->next != NULL)
            p = p->next;
    }
    
    if(!p->gotBonus){
        p_bon tmp = new bonuslist();
        last -> next = tmp;
        tmp -> prev = last;
        tmp -> next = NULL;

        // 1/6 di possibilità di generarlo per terra
        if(rand() % 6 == 0) tmp -> y = h;
        // altrimenti genera sulla platform
        else if(p->y > 2)
           tmp -> y = p -> y - 1;
        else tmp->y = h;

        // poi piazzo la x del bonus a random sulla lunghezza della platform
        tmp -> x = p -> x + rand() % p->len;  // qui c'era un -1 che ho tolto perchè senno stampa i $ a culo
        
        // infine setto il tipo di bonus
        // 1/10 delle volte sarà una vita
        if(rand()%10 == 0)
            tmp->type = 1;
        else 
            tmp->type = 0;

        last = tmp;
        tmp = NULL;
        delete tmp;
        p->gotBonus = true;
    }

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


// da cambiare questa funzione! 
// deve diventare find bonus banalmente e poi a seconda di che bonus 
// è accadono cose
int Bonus::find_bonus(int ps, int lenS, int plx, int ply){
    p_bon iter = current;
    int bonus_type_found = -1;

    while(iter != NULL && iter->x < ps+lenS){
        if(iter->x == plx + ps && iter->y == ply) {
            // mvprintw(24, 20, "win");
            bonus_type_found = iter->type;
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
                delete iter;
                iter = NULL;
            }
            mvprintw(ply, plx, "@");
            mvprintw(ply, plx + 1, " ");
            refresh();
            return bonus_type_found;
        }
        iter = iter->next;
    }
    return bonus_type_found;
}


// int Bonus::lencash(){
//     int cont = 0;
//     p_cash iter = first;
//     while(iter != NULL){
//         iter = iter->next;
//         cont++;
//     }
//     return cont;
// }

