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
        Enemies(Platform*, Bonus*, Player*);
        void generate(int);
        void increase_difficulty(int ps);
        void printEnemies(int,int,int);
    protected:
        int set_y(int);
        char set_avatar(int);
        p_enem current;
        p_enem first;
        p_enem last;
        int fattore_incremento;
        int difficulty;
        Platform* p2;
        Bonus* b2;
        Player* player2;

};