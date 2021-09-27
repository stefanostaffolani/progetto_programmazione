#include "Shoot.hpp"

Shoot::Shoot(){
    this->head = NULL;
    this->tail = NULL;
}

void Shoot::update_bullet(p_bullet iter, int ps){   //TODO: pensare a dove mettere questa funzione
    
    // // if(head != NULL){
    // //     update_bullet_list(ps, iter->next); 
    // //     if((iter->b->get_counter() <= 0) || (mvinch(iter->b->get_position().y, iter->b->get_position().x + iter->b->get_versor()) != 32 &&
    // //         mvinch(iter->b->get_position().y, iter->b->get_position().x + iter->b->get_versor()) != 45)){
    // //             delete iter; 
    // //             iter = NULL;
    // //     }
    // //     else{
    // //         iter->b->move(ps);
    // //         iter->b->decrease_counter();
    // //     }
    // // }   

    
    // if (head == NULL) return NULL;
    // else{
    //     //cout << "ok else" << endl;
    //     p_bullet cur = head;
    //     p_bullet prev = NULL;
    //     while(cur != NULL){
    //         if((cur->b->get_counter() <= 0) || (mvinch(cur->b->get_position().y, cur->b->get_position().x + cur->b->get_versor()) != 32 && mvinch(cur->b->get_position().y, cur->b->get_position().x + cur->b->get_versor()) != 45)){
                
    //             if(prev == NULL){
    //                 //mvprintw(19, 1, "dentro if ==> cancellato head");
    //                 cur = cur->next;
    //                 delete head;
    //                 head = cur;
    //                 //mvprintw(17,1,"%d", cur->counter);
    //                 //cout << "ok head" << endl;
    //             } else{
    //                 //mvprintw(18,1,"dentro el");
    //                 prev->next = cur->next;
    //                 delete cur;
    //                 cur = prev->next;
    //             }
    //         } else{
    //             cur->b->move(ps);
    //             cur->b->decrease_counter();
    //             prev = cur;
    //             cur = cur->next;
    //             //cout << "ok switch cur prev" << endl;
    //         }
    //     }
    // }
}

void Shoot::add_bullet(position p, int v, char avatar, int damage){ 
    if(head == NULL){ // primo proiettile in giro
        head = new bullet_list;
        head->next = NULL;
        head->prev = NULL;
        tail = head;
        head->b = new Bullet(v, p, avatar, damage);
    }
    else{
        p_bullet tmp = new bullet_list;
        tail->next = tmp;
        tmp->next = NULL;
        tmp->prev = tail;
        tail = tmp;
        tail->b = new Bullet(v, p, avatar, damage);
    }
    // if (mvinch(p.y, p.x+v) == 32){
}

 
void Shoot::print_bullet(int ps, int lenS, int versor){
    
    p_bullet iter = head;  

    while(iter != NULL && iter->b->get_position().x < ps + lenS){ // cicla fino a che la nuova x di iter è fuori dallo schermo
            if(versor == 1) iter->b->delete_item(ps-1); // premo d 
            else if(versor == -1) iter->b->delete_item(ps+1); // premo a
            if(iter->b->get_position().x >= ps && iter->b->get_position().x < ps + lenS - 1)
                iter->b->print_item(ps);
            iter = iter->next;
    }

}