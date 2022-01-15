#include <ncurses.h>
#include <time.h>
#include <iostream>
#include "Macro.hpp"


struct node{
        int x;
        int y;
        int len;
        node* next;
        node* prev;
};
typedef struct node* p_node;

 
class Platform{

public:
        Platform();
        void addNode();    
        void printPlatforms(int ps, int versor);           // gli viene passato il puntatore della visuale
        void generate(int ps, int n);                      // genera n nuove platform
        p_node get_current();

protected:
        p_node first;
        p_node last;
        p_node current;
};


