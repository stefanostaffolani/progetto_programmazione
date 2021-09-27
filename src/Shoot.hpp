#include <iostream>
#include <ncurses.h>
#include "Bullet.hpp"

using namespace std;

//#define BULLET '-'
#define RANGE 20

struct bullet_list{
    Bullet* b;
    bullet_list* next;
    bullet_list* prev;
};
 
typedef bullet_list* p_bullet;


class Shoot{
    public:
        Shoot();
        void update_bullet(p_bullet, int);
        void add_bullet(position, int, char, int);
        void print_bullet(int,int,int);
    protected:
        p_bullet head;
        p_bullet tail;
};


