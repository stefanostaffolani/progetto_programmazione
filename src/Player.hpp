#include "Enemies.hpp"
 
class Player : public Item{
public:
    Player(char, Platform*, Bonus*, Enemies*, Shoot*, position);
    
    // fisica di gioco
    void jump(int&);   
    void move(int&);
    void gravity(int&);

    // gestione punti/vita
    void increase_points(int);
    void decrease_life(int);
    void increase_life(int);
    
    // interazioni nemici e danni
    void check_is_hit();
    bool hit_enemy();

    // get
    int get_life();
    int get_points();

    // set
    void set_life(int);
    
    

protected:
    int life;
    int points;
    Platform* p2;
    Bonus* b2;
    Enemies* e2;
    Shoot* s2;
};