#include "Enemy.hpp"
// #include "Platform.hpp"
// #include "Bonus.hpp"
// #include "Player.hpp"
 
struct enemies{
    Enemy* e;
    enemies* next;
    enemies* prev;
};
typedef struct enemies* p_enem;

class Enemies{
    public:
        Enemies(Platform*);
        void generate(int,int,int);
        void addNode(int);
        void removeEnemies(p_enem);

        void update_current(int, int, int);
        void printEnemies(int,int,int);
        int find_enemy(int,int,int,int);

        void move_and_shoot(int,int,int,Shoot*);
        void increase_difficulty(int);

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