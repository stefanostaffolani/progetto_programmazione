//#include "Item.hpp"
#include "Shoot.hpp"
//#include "Player.hpp"
#include <iostream>

class Enemy : public Item {
public:
    Enemy(char, Platform*, position, int, bool);
    bool check_plat_border(int);
    int get_damage();
    int get_type();
    void random_move(int);
    void random_shoot(int, int, int, Shoot*);
    bool check_hit(); 
    /*
    void move();
    */


protected:
    bool on_plat;
    Platform* p2;
    //Player* player2;
    int type;
    int damage;
    void set_damage();
    void increase_damage(int);
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




