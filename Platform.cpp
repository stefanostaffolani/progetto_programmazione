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

void Platform::addNode(){ 
        srand(time(NULL));
        // se non ci sono ancora nodi
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
        else { // altrimenti aggiungo in testa
                p_node tmp = new node;
                tmp -> prev = last;
                tmp -> next = NULL;
                last = tmp;
                tmp = NULL;
                delete tmp;
        }

}

void Platform::printPlatforms(int ps){

        bool screen_void = false;

        if(current -> x + current -> len < ps){
                if(current->next != NULL)
                        current = current->next;
                else screen_void = true;
        }
        if(current -> x < ps + 100 && !screen_void){ // 100 è la larghezza del mio schermo (a caso)
                // comunque di base se entri qua dentro vuol dire che stampi cose

                for(int i = 0; i < current->len; i++){
                        if(current -> x + i >= ps){
                                mvprintw(current->y, current->x + i - ps,"=");
                        }
                }

        }
}

