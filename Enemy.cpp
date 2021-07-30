#include <iostream>
#include <time.h>
#include <ncurses.h>
#include <thread>
#include <chrono>
#include <string.h>
#include "Platform.hpp"
#include "Enemy.hpp"

using namespace std;

Enemy::Enemy(){
    first = new enemies;
    first->y = -10;
    first->x = -10;
    first->lvl = 0;
    first->cont = 0;
    first->passi = rand()%3 + 2;
    first->v = 1;
    first->prev = NULL;
    first->next = NULL;
    last = first;
    current = first;
}

void Enemy::addEnemy(p_node p, int h, int diff){
    p_enem tmp = new enemies;
    last->next = tmp;
    tmp->prev = last;
    tmp->next = NULL;
    tmp->cont = 0;
    tmp->passi = rand()%3 + 2;
    tmp->v = 1;

    // decido difficoltà nemico lvl = {0,1,2}
    if(diff <= 3) tmp->lvl = 0;  // livello 0
    else if(diff > 3 && diff <= 5){ // livello 0 e 1
        if(rand()%3 == 0) tmp->lvl = 0;
        else tmp->lvl = 1;
    }
    else if(diff > 5 && diff <= 8){ // livello 1 e 2
        if(rand()%3 == 0) tmp->lvl = 1;
        else tmp->lvl = 2;
    }
    else tmp->lvl = 2; // livello 3

    // scorro 6 platform avanti per generare il nemico 
    for(int i = 0; i < 6; i++){
        if(p->next != NULL)
            p = p->next;
    }
    // decido se stamparlo su una platform o per terra
    if(rand()%2 == 0) tmp->y = h;
    else tmp -> y = p -> y - 1;
    tmp -> x = p -> x + rand() % p->len;
    last = tmp;
    tmp = NULL;
    delete tmp;
}

void Enemy::printEnemies(int ps, int lenS, int versor){
    // 1) verifica dell'aggiornamento valore current -------------------------
                // se sto andando avanti:
        if(current != NULL){
            if(current -> x < ps && current->next != NULL)
                    current = current -> next;
                    // se sto andando in dietro:
            else if(current -> prev != NULL && current -> prev -> x >= ps)
                    current = current -> prev;
        }

        // 2) stampare da current fino a limite schermo --------------------------
        p_enem iter = current;  
        char enem_avatar[] = "o";

        while(iter != NULL && iter -> x < ps + lenS){ // cicla fino a che la nuova x di iter è fuori dallo schermo
                if(versor == 1) mvprintw(iter->y, iter->x - ps + 1, " "); // premo d 
                else if(versor == -1) mvprintw(iter->y, iter->x - ps - 1, " "); // premo a
                if(iter -> x >= ps && iter -> x < ps + lenS - 1){

       
                    if(iter->lvl == 0) strcpy(enem_avatar, "o");
                    else if(iter->lvl == 1) strcpy(enem_avatar, "x");
                    else if(iter->lvl == 2) strcpy(enem_avatar, "#");

                    mvprintw(iter -> y, iter -> x - ps, enem_avatar);
                }                
                iter = iter->next;
        }
}


void Enemy::move_enem(int ps, int lenS){
    //while(true){
        p_enem iter = current;
        while(iter != NULL && iter -> x < ps + lenS){
            iter->cont++;
            if(iter->cont >= iter->passi){
                iter->cont = 0;
                if(iter->v == -1)
                    iter->v = 1;
                else iter->v = -1;
            }
            mvprintw(iter->y, iter->x - ps, "   ");
            if(iter->v == 1){
                iter->x++;
            }
            if(iter->v == -1){
                iter->x--;
            }
            iter = iter->next;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds (100));
    //}
}


// std::thread Enemy::move_enem_thread(int ps, int lenS){
//     return std::thread([=] { move_enem(ps, lenS); });
// }





