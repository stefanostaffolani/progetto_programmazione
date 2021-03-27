class Player{
public:
    Player();
    void moveRight();
    void moveLeft();
    void jumpPlayer();
    void delay(float seconds);
    int get_x();
    int get_y();

protected:
    int x,y;
};