#include "Platform.hpp"
using namespace std;

struct bonuslist{
        int x;
        int y;
        int type; // 0 -> $, 1 -> Vita
        bonuslist* next;
        bonuslist* prev;
};
 
typedef struct bonuslist* p_bon;
 
class Bonus{
public:
    Bonus(Platform*);
    void generate(int,int);
    void addNode(int);
    void removeBonus(p_bon);

    void update_current(int,int);
    void print_bonus(int, int);
    int find_bonus(int, int, int, int);
protected:
    int set_y(int);
    p_bon first;
    p_bon last;
    p_bon current;
    Platform* p;
};
