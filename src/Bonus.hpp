
struct cashlist{
        int x;
        int y;
        int type; // 0 -> soldi, 1 -> vita
        cashlist* next;
        cashlist* prev;
};
 
typedef struct cashlist* p_cash;

class Bonus{
public:
    Bonus();
    void addCash(p_node, int);
    void printCash(int, int, int);
    bool findCash(int, int, int, int);
    // int lencash();
protected:
    p_cash first;
    p_cash last;
    p_cash current;
};
