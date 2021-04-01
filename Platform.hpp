
class Platform{

public:
        Platform();
        void addNode(int h);    
        void printPlatforms(int ps, int LenS); // gli viene passato il puntatore della visuale
        void generate(int height, int lenS, int ps, int n); // genera n nuove platform
        
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


