struct enemies{
    int x;
    int y;
    int lvl;
    int cont; // contatore interno
    int passi; // numero passi 
    int v; // verso 
    enemies* next;
    enemies* prev;
};
typedef struct enemies* p_enem;

class Enemy{
public:
    Enemy();
    void addEnemy(p_node,int,int);
    void printEnemies(int,int,int);
    //std::thread move_enem_thread(int, int);
    void move_enem(int,int);
    void falling();
    bool findEnemy(int,int,int,int);
protected:
    p_enem first;
    p_enem last;
    p_enem current;
};
