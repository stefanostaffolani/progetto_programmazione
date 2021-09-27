#include <iostream>
#include <chrono>
#include <ncurses.h>
#include "Bullet.hpp"

using namespace std;

//#define BULLET '-'
#define RANGE 20

// struct position{
//     int x,y;
// };

struct bullet_struct{
    Bullet* b;
    bullet_struct *next;
};

typedef bullet_struct* p_bullet;

p_bullet update_bullet_list(p_bullet);

p_bullet add_bullet(p_bullet, position, int, char, int);

void print_bullet_list(p_bullet&, int);

