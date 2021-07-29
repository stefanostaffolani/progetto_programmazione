#include <iostream>
#include <ncurses.h>
#include <time.h>
#include <string.h>
#include "Platform.hpp"
#include "Bonus.hpp"

using namespace std;

Bonus::Bonus(){
    first = new cashlist;
    first->y = -10;
    first->x = -10;
    first->prev = NULL;
    first->next = NULL;
    last = first;
    current = first;
}

void Bonus::addCash(p_node p, int h){
    for(int i = 0; i < 6; i++){
        if(p->next != NULL)
            p = p->next;
    }
    
    if(!p->gotCash){
        p_cash tmp = new cashlist;
        last -> next = tmp;
        tmp -> prev = last;
        tmp -> next = NULL;

        if(rand() % 6 == 0) tmp -> y = h;
        else if(p->y > 2)
           tmp -> y = p -> y - 1;
        else tmp->y = h;

        tmp -> x = p -> x + rand() % p->len;  // qui c'era un -1 che ho tolto perchè senno stampa i $ a culo
        
        last = tmp;
        tmp = NULL;
        delete tmp;
        p->gotCash = true;
    }

}


void Bonus::printCash(int ps, int lenS, int versor){

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
        p_cash iter = current;  

        while(iter != NULL && iter -> x < ps + lenS){ // cicla fino a che la nuova x di iter è fuori dallo schermo
                if(versor == 1) mvprintw(iter->y, iter->x - ps + 1, " "); // premo d 
                else if(versor == -1) mvprintw(iter->y, iter->x - ps - 1, " "); // premo a
                if(iter -> x >= ps && iter -> x < ps + lenS - 1){
                    mvprintw(iter -> y, iter -> x - ps, "$");
                }                
                iter = iter->next;
        }
}


bool Bonus::findCash(int ps, int lenS, int plx, int ply){
    p_cash iter = current;

    // move(30,10);
    // mvprintw(20, 20, "plx+ps: %d", plx + ps);
    // mvprintw(21, 20, "current->x: %d", current->x);    

    // mvprintw(22, 20, "ply: %d", ply);
    // mvprintw(23, 20, "curr->y: %d", current->y);


    while(iter != NULL && iter->x < ps+lenS){
        if(iter->x == plx + ps && iter->y == ply) {
            // mvprintw(24, 20, "win");
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
            return true;
        }
        iter = iter->next;
    }
    return false;
}


int Bonus::lencash(){
    int cont = 0;
    p_cash iter = first;
    while(iter != NULL){
        iter = iter->next;
        cont++;
    }
    return cont;
}

