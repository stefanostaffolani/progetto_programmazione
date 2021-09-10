#include "Item.hpp"

class Enemy : public Item {
public:
    Enemy(char, Platform*, Bonus*, int, int);

    /*
    void generate();
    void move();
    */


protected:
    Item* listofItem;
    int lvl; // valore 0-2
};

