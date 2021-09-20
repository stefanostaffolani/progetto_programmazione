
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
    Bonus();
    void add_bonus(p_node, int);
    void print_bonus(int, int, int);
    int find_bonus(int, int, int, int);
    // int lencash();
protected:
    p_bon first;
    p_bon last;
    p_bon current;
};
