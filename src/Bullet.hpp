#include "Item.hpp"

class Bullet : public Item{
    public:
        Bullet(int, position, char, int);

        // incr-decr
        void decrease_counter();
        //void increase_damage(int);

        void hit_something();
        void set_damage(int);
        
        // get
        int get_counter();
        int get_damage();
        bool get_hit();
        char get_avatar();   // valutare se mettere direttamente in item

    protected:
        int counter;
        int damage;
        bool hit;
}; 
