#include "Bonus.hpp"
#include <ncurses.h>
#include <thread>
#include <chrono>

#define INIT_X 1
#define END_X 75
#define HEIGHT 12
#define SPACE 32
#define EQUAL 61
#define DOLLAR 36
#define PIPE 124
#define P_DAMAGE 10

struct position{
    int x;
    int y;
};


class Item{
    public:
        Item(char, position, int);
        void move(int);
        void set_x(int);
        position get_position();
        void set_versor(int);
        int get_versor();
        void print_item(int);
        void delete_item(int);

    protected:
        position pos;
        int versor;
        char avatar;
};