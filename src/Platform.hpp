
struct node{
        int x;
        int y;
        int len;
        bool gotCash;
        node* next;
        node* prev;
};
typedef struct node* p_node;


class Platform{

public:
        Platform();
        void addNode(int h);    
        void printPlatforms(int ps, int LenS, int versor); // gli viene passato il puntatore della visuale
        void generate(int height, int lenS, int ps, int n); // genera n nuove platform
        p_node get_current() { return current; }

protected:
        p_node first;
        p_node last;
        p_node current;
};


