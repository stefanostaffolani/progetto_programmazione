#include "Item.hpp"

#define RANGE 20

class Bullet : public Item{
    public:
        Bullet(int, position, char, int);
        void decrease_counter();
        void hit_something();
        void set_damage(int);
        void increase_damage(int);
        int get_counter();
        int get_damage();
        bool get_hit();

    protected:
        int counter;
        int damage;
        bool hit;
}; 