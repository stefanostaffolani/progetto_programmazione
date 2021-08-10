#include "Item.hpp"

#define Y_JUMP 5

class Player : public Item{
public:
    Player(int, int, char, Platform*, Bonus*);
    void printPlayer();
    void jump(int&);
    void increase_points(int);
    int get_life();
    int get_points();
    void collision_jump();
    void gravity(int&);


protected:
    // int x,y;
    // int versor;    // versor = 1 go dx versor = -1 go sx versor = 0 don't move
    int life;
    int points;
    
};