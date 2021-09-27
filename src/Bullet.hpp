#include "Item.hpp"

#define RANGE 20

class Bullet : public Item{
    public:
        Bullet(int, position, char, int);
        void decrease_counter();
        bool hit_something();
        void set_damage(int);
        void increase_damage(int);
        int get_counter();

    protected:
        int counter;
        int damage;
};