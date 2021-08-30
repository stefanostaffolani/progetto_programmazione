//#include "Item.hpp"
#include "Shoot.hpp"

#define Y_JUMP 5
 
class Player : public Item{
public:
    Player(char, Platform*, Bonus*, int, int);
    void printPlayer();
    void jump(int&, p_bullet&);
    void increase_points(int);
    void decrease_life(int);
    bool is_hit();
    int get_life();
    int get_points();
    void gravity(int&, p_bullet&);


protected:
    // int x,y;
    // int versor;    // versor = 1 go dx versor = -1 go sx versor = 0 don't move
    int life;
    int points;
    
};