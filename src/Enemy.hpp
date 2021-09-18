#include "Item.hpp"
#include <iostream>

class Enemy : public Item {
public:
    Enemy(char, Platform*, Bonus*, int, int, int);
    bool check_plat_border();
    //void generate_on_platform(int);

    /*
    void generate();
    void move();
    */


protected:
    bool on_plat;
    // Item* listofItem;
    // int lvl; // valore 0-2
    Platform* p2;
    Bonus* b2;
    int type;
    int damage;
    void set_damage();
};



/*
    3 nemici(type)
    base => sta fermo e fa danno se lo tocchi (0)
    medio => si muove(forse salta) e se lo tocchi ti fa male (1)
    forte => è uguale al medio ma spara(*) (2)
*/

/* cosa deve avere Enemy:
    -eredita move da item
    -attributo vita, danno
    tipo di nemico:
        0,1,2



*/




