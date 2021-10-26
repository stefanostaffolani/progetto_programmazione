#include "Player.hpp"

using namespace std;

Player::Player(char avatar, Platform* p1, Bonus* b1, Enemies* e1, Shoot* s1, position pos):Item(avatar, pos, 0){
    life = 100;
    points = 0;
    p2 = p1;
    b2 = b1;
    e2 = e1;
    s2 = s1;
}
 
int Player::get_life(){return this->life;}

int Player::get_points(){return this->points;}

void Player::increase_points(int n){this->points += n;}

bool Player::hit_enemy(){
    return (mvinch(this->pos.y, this->pos.x) == (int)'o' || mvinch(this->pos.y, this->pos.x) == (int)'O');
}

void Player::move(int& ps){
    if((this->versor == -1) && (this->pos.x < 20) && (ps >= 1)){
        ps--;
    }else if ((this->versor == 1) && (this->pos.x > 55)){
        ps++;
    }
    else Item::move(0);
    this->print_item(0);
    s2->update_bullet(ps, 75);
    p2->printPlatforms(ps, 75, this->versor);
    b2->print_bonus(ps, 75, this->versor);
    e2->printEnemies(ps, 75, this->versor);
}

void Player::decrease_life(int n){this->life -= n;}
void Player::increase_life(int n){this->life += n;}
void Player::set_life(int n) {this->life = n;}

void Player::check_is_hit(){
    p_bullet iter = s2->get_head();
    bool game_over = false;
    while(iter != NULL && !game_over){
        if(iter->b->get_position().x == this->pos.x && iter->b->get_position().y == this->pos.y && (iter->b->get_avatar() != '-')){
            this->decrease_life(iter->b->get_damage());
            if(this->get_life() <= 0) game_over = true;
        }
        iter = iter->next;
    }

}

void Player::jump(int& ps){
    int i = 0;
    char c;
    bool hit_something = false;
    position diagonale, sopra;
    while((i < Y_JUMP) && !(hit_something)){

        e2->move_and_shoot(75,ps,this->pos.x,s2);     //aggiorna i nemici

        c = getch();
        diagonale = {this->pos.x+this->versor, this->pos.y - 1};
        sopra = {this->pos.x, this->pos.y - 1};
        
        if(c == (int)' ') s2->add_bullet(this->pos, this->versor, '-', P_DAMAGE);   //per sparare
        
        if (mvinch(diagonale.y, diagonale.x) == (int)' '){
            this->delete_item(0);
            if(mvinch(sopra.y, sopra.x) == (int)' '){   //perchè il move cancella
                this->pos.y--;
                this->move(ps);
            }else{
                this->delete_item(0);
                this->pos.y--;
                this->pos.x += this->versor;
                this->print_item(0);
            }
            i++;
        } else{
            hit_something = true;
        }
        s2->update_bullet(ps, 75);   //TODO mettere lenS al posto di 75
        p2->printPlatforms(ps,75, versor);
    }
    gravity(ps);
}

void Player::gravity(int& ps){   //TODO: gestire caso salto su proiettili (magari mettendo hit_something = false???)
    bool hit_something = false;
    char c;
    if (mvinch(this->pos.y + 1, this->pos.x) != SPACE && mvinch(this->pos.y + 1, this->pos.x) != DOLLAR && mvinch(this->pos.y + 1, this->pos.x) != 86) hit_something = true;  //controllare 
    else hit_something = false;
    position diagonale, sotto, laterale;
    while(!(hit_something)){
        
        e2->move_and_shoot(75,ps,this->pos.x,s2);   //per i nemici

        //per sparare
        c = getch();
        if(c == SPACE) s2->add_bullet(this->pos, this->versor, '-', P_DAMAGE);
        
        diagonale = {this->pos.x + versor, this->pos.y + 1};
        sotto = {this->pos.x, this->pos.y+1};
        laterale = {this->pos.x+this->versor, this->pos.y};
        if (mvinch(sotto.y, sotto.x) == (int)'=' || this->pos.y == HEIGHT){   // ho qualcosa sotto
            hit_something = true;
        }
        else if(mvinch(diagonale.y, diagonale.x) != SPACE){
            hit_something = true;
            if(mvinch(diagonale.y, diagonale.x) == (int)'-' || mvinch(diagonale.y, diagonale.x) == (int)'*'){
                hit_something = false;
                this->delete_item(0);
                this->pos.x += versor;
                this->pos.y++;
                this->print_item(0);
            }
            else if (mvinch(diagonale.y, diagonale.x) == (int)'$' || mvinch(diagonale.y, diagonale.x) == (int)'V'){
                this->delete_item(0);
                this->pos.y++;
                this->move(ps);
            }else if(mvinch(diagonale.y, diagonale.x) == (int)'|'){
                this->delete_item(0);
                this->pos.y = HEIGHT;
                this->pos.x = INIT_X;
                this->print_item(0);
                refresh();
            }else if(mvinch(diagonale.y,diagonale.x) == (int)'o' || mvinch(diagonale.y,diagonale.x) == (int)'O'){
                this->delete_item(0);
                this->pos.y++;
                this->print_item(0);
                refresh();
            }else if (mvinch(sotto.y, sotto.x) == (int)' '){
                this->delete_item(0);
                this->move(ps);
            }
            //vedere se ne servono altri
        }
        else{
            if(mvinch(laterale.y, laterale.x) == (int)'=' || mvinch(laterale.y, laterale.x) == (int)'o' || mvinch(laterale.y, laterale.x) == (int)'O'){   // perchè potrebbe cancellare lo spigolo della platform
                this->delete_item(0);
                this->pos.x+=versor;
                this->pos.y++;
                this->print_item(0);
            }
            else{
                this->move(ps);
                this->delete_item(0);
                this->pos.y++;
                this->print_item(0);
            }
    }        
        s2->update_bullet(ps,75);
        p2->printPlatforms(ps, 75, versor);
    }
}