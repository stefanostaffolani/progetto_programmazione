#include "Bonus.hpp"

#define INIT_X 1
#define END_X 75
#define HEIGHT 12
#define LENGTH 75
#define SPACE 32
#define EQUAL 61
#define DOLLAR 36
#define PIPE 124
#define P_DAMAGE 10

struct position{
    int x;
    int y;
};

    // versor = 1 go dx versor = -1 go sx 

class Item{
    public:
        Item(char, position, int);
        
        // fisica
        void move(int);
        
        // set
        void set_x(int);
        void set_versor(int);

        // get
        position get_position();
        int get_versor();
        
        // stampa 
        void print_item(int);
        void delete_item(int);

    protected:
        position pos;
        int versor;
        char avatar;
};