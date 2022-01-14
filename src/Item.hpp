#include "Bonus.hpp"

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