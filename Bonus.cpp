#include <iostream>
#include <ncurses.h>
#include <time.h>
#include <string.h>
#include "Platform.hpp"
#include "Bonus.hpp"

using namespace std;

Bonus::Bonus(){
    first = NULL;
    last = NULL;
    current = NULL;
}

void Bonus::addCash(p_node p, int h){
    for(int i = 0; i < 6; i++){
        if(p->next != NULL)
            p = p->next;
    }
    
    int r = rand() % 3;

    if(first == NULL){
        first = new cashlist;
        first -> x = p -> x + rand() % p->len - 1; // valore a caso dentro la platform 
        first -> y = p -> y - 1;

        first -> prev = NULL;
        first -> next = NULL;
        last = first;
        current = first;
    }
    else { // altrimenti aggiungo in testa  --------------------------------
        if(!p->gotCash){
            p_cash tmp = new cashlist;
            last -> next = tmp;
            tmp -> prev = last;
            tmp -> next = NULL;

            if(rand() % 6 == 0) tmp -> y = h;
            else
                tmp -> y = p -> y - 1;
            
            tmp -> x = p -> x + rand() % p->len - 1;
           
            last = tmp;
            tmp = NULL;
            delete tmp;
            p->gotCash = true;
        }
    }
}


void Bonus::printCash(int ps, int lenS, int versor){

    // 1) verifica dell'aggiornamento valore current -------------------------
                // se sto andando avanti:
        if(current -> x < ps && current->next != NULL)
                current = current -> next;
                // se sto andando in dietro:
        else if(current -> prev != NULL && current -> prev -> x >= ps)
                current = current -> prev;

        // 2) stampare da current fino a limite schermo --------------------------
        p_cash iter = current;  

        while(iter != NULL && iter -> x < ps + lenS){ // cicla fino a che la nuova x di iter è fuori dallo schermo
                if(versor == 1) mvprintw(iter->y, iter->x - ps, "  "); 
                else if(versor == -1) mvprintw(iter->y, iter->x - ps - 1, "  ");
                if(iter -> x >= ps && iter -> x < ps + lenS - 1){
                    mvprintw(iter -> y, iter -> x - ps, "$");
                }                
                iter = iter->next;
        }
}


bool Bonus::findCash(int ps, int lenS, int plx, int ply){
    p_cash iter = current;
    while(iter != NULL && iter->x < ps+lenS){
        if(iter->x == plx && iter->y == ply) {
            if(iter == current){ 
                if(iter != first)
                    current = iter->prev;
                else if(iter != last)
                    current = iter -> next;
                else 
                    current = NULL;
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
                iter = NULL;
                delete iter;
            }
            mvprintw(ply, plx, " ");
            return true;
        }
        iter = iter->next;
    }
    return false;
}


