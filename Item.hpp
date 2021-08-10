#include "Platform.hpp"
#include "Bonus.hpp"
#include <ncurses.h>
#include <thread>
#include <chrono>

#define INIT_X 1
#define END_X 70
#define HEIGHT 12


class Item{
    public:
        Item(int, int, char, Platform*, Bonus*);
        void move(int&);
        void set_x(int);
        int get_x();
        int get_y();
        void set_versor(int);
        int get_versor();

    protected:
        int x,y;
        int versor;
        char avatar;
        Platform* p2;
        Bonus* b2;
};