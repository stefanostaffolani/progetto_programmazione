#include <iostream>
#include <ncurses.h>
#include <time.h>
#include "Platform.hpp"
#include "Macro.hpp"

using namespace std;

Platform::Platform(){
        first = NULL;
        last = NULL;
        current = NULL;
}
 
// aggiunge una platform nella lista
void Platform::addNode(){ 

        // se non ci sono ancora nodi 
        if(first == NULL){ 
               
                first = new node;               // il primo nodo(first), prima nullo, punta a un nuovo nodo 
                first -> x = PLAT_X_POS;                // posizione x della platform [ x==== ]
                first -> y = rand() % 2 + 10;   // posizione y della platform (valore random e il player deve poterci arrivare)
                first -> len = rand() % 10 + 5; // lunghezza len della platform [ 01..===t ] len = t                     
                
                // setto prev e next a null perchè è il primo nodo
                first -> prev = NULL;           
                first -> next = NULL;

                // i puntatori last e current puntano a first
                last = first;               
                current = first;
        
        }
        else { // altrimenti aggiungo in testa  
                
                p_node tmp = new node;         

                // sistema della dinamica di puntatori, last punta all'ultimo nodo appena creato tmp, current e first non vengono cambiati           
                tmp -> prev = last;
                tmp -> next = NULL;
                last -> next = tmp; 
                last = tmp;

                // la x del nuovo nodo è uguale alla x del precedente più la lunghezza e un valore random 
                tmp -> x = tmp -> prev -> x + tmp -> prev -> len + rand() % 2 + 5; 

                // la y del nuovo nodo è uguale alla y del precedente più un range randomico anche negativo 
                do {
                        tmp -> y = tmp -> prev -> y + rand() % 4 - rand() % 3;
                
                // finchè il valore che ho trovato entra nello schermo 
                } while(tmp -> y < 4 || tmp -> y > HEIGHT - 2);

                tmp -> len = rand() % 10 + 5;   // lunghezza len della platform [ 01..===t ] len = t
                
                tmp = NULL;
                delete tmp;
        }

} 


void Platform::printPlatforms(int ps, int versor){ 

        // 1) verifica dell'aggiornamento valore current 
                // se sto andando avanti:
        if(current -> x + current -> len < ps)          // se x+len di current è fuori dallo schermo a sinistra
                current = current -> next;              
                // se sto andando in dietro:
        else if(current -> prev != NULL && current -> prev -> x + current -> prev -> len >= ps) // se x+len è fuori dallo schermo a destra 
                current = current -> prev;                                                     


        // 2) stampo le platform da current fino a che o finisco o trovo una x fuori dallo schermo
        p_node iter = current;   

        while(iter != NULL && iter -> x < ps + LENGTH){ 

                // a seconda della direzione(versor) cancello la = della platform degli estremi poichè lo schermo si è mosso  
                if(versor == 1) mvprintw(iter->y, iter->x + iter->len - ps, " "); 
                else if(versor == -1) mvprintw(iter->y, iter->x - ps - 1, " ");
                
                // stampo = della platform da x fino a x+len controllando che non esca dallo schermo
                for(int i = 0; i < iter->len; i++){
                        if(iter -> x + i >= ps && iter -> x + i < ps + LENGTH - 1)
                                mvprintw(iter -> y, iter -> x + i - ps, "=");
                }
                iter = iter->next;
        }

} 

/* se l'ultima platform che è stata generata entra nello schermo
*  chiama per n volte la funzione addNode che aggiunge un nuovo nodo 
*/
void Platform::generate(int ps, int n){
        if(last->x < ps + LENGTH){ 
                for(int i = 0; i < n; i++)
                      addNode();                          
        }
}

p_node Platform::get_current(){ return this->current; }
