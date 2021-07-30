#include "Platform.hpp"
#include "Bonus.hpp"
#include "Enemy.hpp"

#define HEIGHT 12
#define INIT_X 1
#define END_X 70
#define Y_JUMP 5
#define PLAYER_AVATAR "@"

class Player{
public:
    Player(int, int, p_node, Platform*, Bonus*, Enemy*);
    void jump(int&);
    void move(int&);
    void set_x(int);
    void increase_points(int);
    int get_x();
    int get_y();
    int get_life();
    int get_points();
    void collision_jump();
    void gravity(int&);
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
    int life;
    int points;
    p_node plat_sx;
    p_node plat_dx;
    p_node plat_cx;
    p_node initial;
    Platform* p2;
    Bonus* b2;
    Enemy* enem2;
};