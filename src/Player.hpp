//#include "Item.hpp"
#include "Enemies.hpp"
//#include "Shoot.hpp"

#define Y_JUMP 5
 
class Player : public Item{
public:
    Player(char, Platform*, Bonus*, Enemies*, int, int);
    void jump(int&, p_bullet&);
    void move(int&, p_bullet&);
    void increase_points(int);
    void decrease_life(int);
    void increase_life(int);
    bool is_hit();
    int get_life();
    void set_life(int);
    int get_points();
    void gravity(int&, p_bullet&);
    bool hit_enemy();


protected:
    // int x,y;
    // int versor;    // versor = 1 go dx versor = -1 go sx versor = 0 don't move
    int life;
    int points;
    Platform* p2;
    Bonus* b2;
    Enemies* e2;
};