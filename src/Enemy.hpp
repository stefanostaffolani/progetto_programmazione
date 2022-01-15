#include "Shoot.hpp"

class Enemy : public Item {
public:
    Enemy(char, Platform*, position, int, bool, int);
    
    // check per movimento
    bool check_plat_border(int);
    
    // azioni random del nemico
    void random_move(int);
    void random_shoot(int, int, int, Shoot*);
    
    // decrementa vita
    void decrease_life(int);
    
    // get
    int get_life();
    int get_damage();
    int get_type();


protected:
    bool on_plat;
    Platform* p2;
    int life;
    int type;
    int damage;
    void increase_damage(int);
};



/*
    2 nemici(type)
    base => sta fermo e fa danno se lo tocchi (0)
    forte => si muove e spara(*) (2)
*/

/* cosa deve avere Enemy:
    -eredita move da item
    -attributo vita, danno
    tipo di nemico
*/




