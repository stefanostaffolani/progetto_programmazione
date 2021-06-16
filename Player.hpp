#include "Platform.hpp"
class Player{
public:
    Player(int, int, p_node);
    void printPlayer();
    void moveRight();
    void moveLeft();
    void set_x(int);
    int get_x();
    int get_y();
    void collision_jump(int, int, int);
    void gravity(int , int, int);
    void set_versor(int);
    int get_versor();
    void update_platform();

protected:
    int x,y;
    int versor;    // versor = 1 go dx versor = -1 go sx versor = 0 don't move
    p_node plat_sx;
    p_node plat_dx;
};