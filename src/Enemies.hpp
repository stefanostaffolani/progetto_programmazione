#include "Enemy.hpp"
 
struct enemies{
    Enemy* e;
    enemies* next;
    enemies* prev;
};
typedef struct enemies* p_enem;

class Enemies{
    public:
        Enemies(Platform*);
        void generate(int,int);
        void addNode(int);
        void removeEnemies(p_enem&);
        void delete_base_enemy(position, int);

        void update_current(int, int);
        void printEnemies(int,int);
        
        void move_and_shoot(int,int,Shoot*);
        void increase_difficulty(int);
        void check_is_hit(int,Shoot*);

        int get_difficulty();


    protected:
        int set_y(int);
        char set_avatar(int);
        p_enem current;
        p_enem first;
        p_enem last;
        int fattore_incremento;
        int difficulty;
        Platform* p2;
};