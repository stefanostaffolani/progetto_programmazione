#include "Platform.hpp"

#define HEIGHT 12
#define INIT_X 1
#define END_X 70
#define Y_JUMP 5

class Player{
public:
    Player(int, int, p_node);
    void printPlayer();
    //void moveRight();
    //void moveLeft();
    void jump();
    void move();
    void set_x(int);
    int get_x();
    int get_y();
    void collision_jump();
    void gravity();
    void set_versor(int);
    int get_versor();
    bool hit_plat_cx();
    void update_platform();
    p_node get_platdx();
    p_node get_platcx();
    p_node get_platsx();

protected:
    int x,y;
    int versor;    // versor = 1 go dx versor = -1 go sx versor = 0 don't move
    p_node plat_sx;
    p_node plat_dx;
    p_node plat_cx;
    p_node initial;
};