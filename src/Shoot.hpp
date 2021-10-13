#include "Bullet.hpp"

using namespace std;

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
        void update_bullet(int, int);
        void add_bullet(position, int, char, int);
        void print_bullet(int,int);
        void remove_bullet(p_bullet&);
        p_bullet get_head();

    protected:
        p_bullet head;
        p_bullet tail;
};


