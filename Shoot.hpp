#include <iostream>
#include <thread>
#include <chrono>
#include <ncurses.h>
#include "Item.hpp"

using namespace std;

#define BULLET '-'
#define RANGE 10

// struct position{
//     int x,y;
// };

struct bullet_struct{
    int versor;
    position pos;
    int counter;
    bullet_struct *next;
};

typedef bullet_struct* p_bullet;

p_bullet update_bullet_list(p_bullet);

p_bullet add_bullet(p_bullet, position, int);

void print_bullet_list(p_bullet&);
