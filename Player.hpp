#include "Platform.hpp"

#define HEIGHT 12
#define INIT_X 1
#define END_X 70
#define Y_JUMP 5
#define PLAYER_AVATAR "@"
#define RANGE 10
#define BULLET "-"

class Player{
public:
    Player(int, int, int&);
    void printPlayer();
    void jump(Platform*);
    void move(Platform*);
    void set_x(int);
    void shoot();
    int get_x();
    int get_y();
    void gravity(Platform*);
    void set_versor(int);
    int get_versor();
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
    int pointer_screen;
};