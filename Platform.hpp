
class Platform{

public:
        Platform();
        void addNode();
        void printPlatforms(int ps); // gli viene passato il puntatore della visuale

protected:

        struct node{
                int x;
                int y;
                int len;
                node* next;
                node* prev;
        };
        typedef struct node* p_node;
        p_node first;
        p_node last;
        p_node current;

};


