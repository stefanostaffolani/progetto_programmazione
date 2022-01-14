#include <ncurses.h>
#include "Field.hpp"
#include "Player.hpp"
using namespace std;

class Game{
    public:
        Game();
        void game_loop();
        void kbd_input();
        void game_print();
        void game_check_enemy_collision();
        void game_generate();
        void game_bonus();
        void game_dynamics();

    protected:
        Field* field;
        Platform* p1;
        Bonus* b1;
        Shoot* s1;
        Enemies* E;
        Player* player;
        int ps,c;
        bool gameOver;
};