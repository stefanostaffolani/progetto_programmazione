#include "Shoot.hpp"

Shoot::Shoot(){
    this->head = NULL;
    this->tail = NULL;
}

void Shoot::update_bullet(int ps, int lenS){   //TODO: pensare a dove mettere questa funzione
    
    p_bullet iter = head;
    while(iter != NULL){
        mvprintw(18,20,"entro nel while");
        iter->b->decrease_counter();
        if(iter->b->get_counter() < 0 || iter->b->get_hit() || iter->b->get_position().x > lenS || iter->b->get_position().x < 1)
            remove_bullet(iter);
        else{
            iter->b->hit_something();
            
            iter->b->move(0);
        }
        if(iter != NULL)
            iter = iter->next;
    }

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

 
void Shoot::print_bullet(int ps, int lenS){
    
    p_bullet iter = head;  
    while(iter != NULL){
        iter->b->print_item(0);
        iter = iter->next;
    }

    // while(iter != NULL && iter->b->get_position().x < ps + lenS){ // cicla fino a che la nuova x di iter è fuori dallo schermo
    //         if(versor == 1) iter->b->delete_item(ps-1); // premo d 
    //         else if(versor == -1) iter->b->delete_item(ps+1); // premo a
    //         if(iter->b->get_position().x >= ps && iter->b->get_position().x < ps + lenS - 1)
    //             iter->b->print_item(ps);
    //         iter = iter->next;
    // }

}


p_bullet Shoot::get_head(){return this->head;}


void Shoot::remove_bullet(p_bullet& iter){
    if(iter == head){
        if(head->next == NULL){
            head = NULL;
            tail = NULL;
        }
        else{
            head = head->next;
            head->prev = NULL;
        }
    }
    else if(iter == tail){
        tail = tail->prev;
        tail->next = NULL;
    }
    else{
        iter->prev->next = iter->next;
        iter->next->prev = iter->prev;
    }
    
    delete iter;
    iter = NULL;
}


