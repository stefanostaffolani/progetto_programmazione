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
        // se non ci sono ancora nodi -------------------------------------------
        if(first == NULL){
                first = new node;
                first -> x = 40; // un valore a caso che può essere anche k
                first -> y = rand() % 2 + 10;  // siccome il player deve poterci saltare do valore rand
                first -> len = 10;

                if(rand()%4 == 0)
                        first -> gotBonus = false;
                else    
                        first -> gotBonus = true;
                
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
                if(rand()%4 == 0)
                        tmp -> gotBonus = false;
                else 
                        tmp -> gotBonus = true;

                tmp -> x = tmp -> prev -> x + tmp -> prev -> len + rand() % 2 + 5;
                do {
                        tmp -> y = tmp -> prev -> y + rand() % 4 - rand() % 3;
                } while(tmp -> y < 4 || tmp -> y > h - 2);
                tmp -> len = rand() % 10 + 5;
                last = tmp;
                tmp = NULL;
                delete tmp;
        }

} // fine funzione addNode() ==========================================================




void Platform::printPlatforms(int ps, int lenS, int versor){ // ===================================

        // 1) verifica dell'aggiornamento valore current -------------------------
                // se sto andando avanti:
        if(current -> x + current -> len < ps)
                current = current -> next;
                // se sto andando in dietro:
        else if(current -> prev != NULL && current -> prev -> x + current -> prev -> len >= ps)
                current = current -> prev;

        // 2) stampare da current fino a limite schermo --------------------------
        p_node iter = current;   

        while(iter != NULL && iter -> x < ps + lenS){ // cicla fino a che la nuova x di iter è fuori dallo schermo
                if(versor == 1) mvprintw(iter->y, iter->x + iter->len - ps, " "); 
                else if(versor == -1) mvprintw(iter->y, iter->x - ps - 1, " ");
                for(int i = 0; i < iter->len; i++){
                        if(iter -> x + i >= ps && iter -> x + i < ps + lenS - 1)
                                mvprintw(iter -> y, iter -> x + i - ps, "=");
                }
                iter = iter->next;
        }

} // fine funzione printPlatforms() ==================================================




void Platform::generate(int height, int lenS, int ps, int n){
        if(last->x < ps + lenS){ // genera platform se l'ultima entra nello schermo
                for(int i = 0; i < n; i++)
                      addNode(height);                          
        }
}
