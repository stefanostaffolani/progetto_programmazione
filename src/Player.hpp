//#include "Item.hpp"
#include "Enemies.hpp"
//#include "Shoot.hpp"

#define Y_JUMP 5
 
class Player : public Item{
public:
    Player(char, Platform*, Bonus*, Enemies*, Shoot*, position);
    void jump(int&);
    void move(int&);
    void increase_points(int);
    void decrease_life(int);
    void increase_life(int);
    bool is_hit();
    int get_life();
    void set_life(int);
    int get_points();
    void gravity(int&);
    bool hit_enemy();


protected:
    // int x,y;
    // int versor;    // versor = 1 go dx versor = -1 go sx versor = 0 don't move
    int life;
    int points;
    Platform* p2;
    Bonus* b2;
    Enemies* e2;
    Shoot* s2;
};