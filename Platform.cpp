#include <iostream>
#include <ncurses.h>
#include <time.h>
#include "Platform.hpp"
using namespace std;

Platform::Platform(){
        first = NULL;
        last = NULL;
        current = NULL;
}


void Platform::addNode(int h){ // ======================================================
        srand(time(NULL));
        // se non ci sono ancora nodi -------------------------------------------
        if(first == NULL){
                first = new node;
                first -> x = 40; // un valore a caso che può essere anche k
                first -> y = rand() % 10 + 1;  // siccome il player deve poterci saltare do valore rand
                //first -> len = rand() % 10 + 5;
                first -> len = 10;
                first -> prev = NULL;
                first -> next = NULL;
                last = first;
                current = first;
        }
        else { // altrimenti aggiungo in testa  --------------------------------
                p_node tmp = new node;
                last -> next = tmp;
                tmp -> prev = last;
                tmp -> next = NULL;
                tmp -> x = tmp -> prev -> x + tmp -> prev -> len + rand() % 20 + 10;
                do {
                        tmp -> y = tmp -> prev -> y + rand() % 10 - rand() % 10;
                } while(tmp -> y < 0 || tmp -> y > h);
                tmp -> len = rand() % 10 + 5;
                last = tmp;
                tmp = NULL;
                delete tmp;
        }

} // fine funzione addNode() ==========================================================




void Platform::printPlatforms(int ps, int lenS){ // ===================================

        // 1) verifica dell'aggiornamento valore current -------------------------
                // se sto andando indietro:
        if(current -> x + current -> len < ps)
                current = current -> next;
                // se sto andando in avanti:
        else if(current -> prev != NULL && current -> prev -> x + current -> prev -> len >= ps)
                current = current -> prev;

        // 2) stampare da current fino a limite schermo --------------------------
        p_node iter = current;

        while(iter != NULL && iter -> x < ps + lenS){ // cicla fino a che la nuova x di iter è fuori dallo schermo
                for(int i = 0; i < iter->len; i++){
                        if(iter -> x + i >= ps && iter -> x + i < ps + lenS)
                                mvprintw(iter -> y, iter -> x + i - ps, "=");
                }
                iter = iter->next;
        }

} // fine funzione printPlatforms() ==================================================

