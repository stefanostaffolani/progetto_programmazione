#include "Bullet.hpp"

using namespace std;

struct bullet_list{   //lista di proiettili
    Bullet* b;
    bullet_list* next;
    bullet_list* prev;
};
 
typedef bullet_list* p_bullet;


class Shoot{
    public:
        Shoot();
        void update_bullet(int);   // aggiorna la lista dei proiettili
        void add_bullet(position, int, char, int);
        void remove_bullet(p_bullet&);
        p_bullet get_head();

    protected:
        p_bullet head;
        p_bullet tail;
};


