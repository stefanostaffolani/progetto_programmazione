#include "Platform.hpp"
#include "Bonus.hpp"
#include <ncurses.h>
#include <thread>
#include <chrono>

#define INIT_X 1
#define END_X 70
#define HEIGHT 12
 
struct position{
    int x;
    int y;
};


class Item{
    public:
        Item(char, int, int);
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