#include "Shoot.hpp"

p_bullet update_bullet_list(p_bullet head, int ps){   //TODO: pensare a dove mettere questa funzione
    if (head == NULL) return NULL;
    else{
        //cout << "ok else" << endl;
        p_bullet cur = head;
        p_bullet prev = NULL;
        while(cur != NULL){
            if((cur->b->get_counter() <= 0) || (mvinch(cur->b->get_position().y, cur->b->get_position().x + cur->b->get_versor()) != 32 && mvinch(cur->b->get_position().y, cur->b->get_position().x + cur->b->get_versor()) != 45)){
                if(prev == NULL){
                    //mvprintw(19, 1, "dentro if ==> cancellato head");
                    cur = cur->next;
                    delete head;
                    head = cur;
                    //mvprintw(17,1,"%d", cur->counter);
                    //cout << "ok head" << endl;
                } else{
                    //mvprintw(18,1,"dentro el");
                    prev->next = cur->next;
                    delete cur;
                    cur = prev->next;
                }
            } else{
                cur->b->move(ps);
                cur->b->decrease_counter();
                prev = cur;
                cur = cur->next;
                //cout << "ok switch cur prev" << endl;
            }
        }
        return head;
    }
}

p_bullet add_bullet(p_bullet head, position p, int v, char bullet, int damage){   //vedere se serve ps
    if (mvinch(p.y, p.x+v) == 32){
        p_bullet tmp = new bullet_struct;
        tmp->b = new Bullet(v, p, damage, bullet);
        // tmp->b->bullet = bullet;
        // tmp->pos.x = p.x + v;
        // tmp->pos.y = p.y;
        // tmp->counter = RANGE;
        // tmp->versor = v;
        tmp->next = head;
        return tmp;
        }
    else return head;
}


void print_bullet_list(p_bullet& head, int ps){
    p_bullet iter;
    for(iter = head; iter != NULL; iter=iter->next){
        //mvprintw(iter->b->get_position().y, iter->b->get_position().x, " ");
        iter->b->delete_item(ps);
    }
    //mvprintw(15, 15, "ok1");
    //cout << "ok 1 ciclo print" << endl;
    head = update_bullet_list(head, ps);
    //mvprintw(15, 15, "ok2");

    for(iter = head; iter != NULL; iter=iter->next){
        //mvprintw(iter->b->get_position().y, iter->b->get_position().x, "%c", iter->b->print_item(ps));
        iter->b->print_item(ps);
    }
    // while(head != NULL){
    //     //mvprintw(head->pos.y, head->pos.x, " ");
    //     mvprintw(head->pos.y, head->pos.x, "%c", BULLET);
    //     //std::this_thread::sleep_for(std::chrono::milliseconds (100));
    //     //mvprintw(head->pos.y, head->pos.x, " ");
    //     head = head->next;
    // }
    //mvprintw(15, 15, "ok3");

    //cout << "ok 2 ciclo print" << endl;
}