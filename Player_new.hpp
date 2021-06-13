class Player{
public:
    Player();
    void moveRight();
    void moveLeft();
    int get_x();
    int get_y();
    void collision_jump(int, int, int);
    void gravity(int , int, int);
    void set_versor(int);
    int get_versor();

protected:
    int x,y;
    int versor;
    int life;    // versor = 1 go dx versor = -1 go sx versor = 0 don't move
};