#include "Item.hpp"

class Enemy : public Item {
public:
    Enemy(char, Platform*, Bonus*, int, int);
    bool check_plat_border();
    void generate_on_platform(int);

    /*
    void generate();
    void move();
    */


protected:
    bool on_plat;
    Item* listofItem;
    int lvl; // valore 0-2
};

