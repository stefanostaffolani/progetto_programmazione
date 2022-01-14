#include "Shoot.hpp"

Shoot::Shoot(){
    this->head = NULL;
    this->tail = NULL;
}

void Shoot::update_bullet(int ps, int lenS){
    
    p_bullet iter = head;
    while(iter != NULL){
        iter->b->decrease_counter();  
        
        //cancella se tocca qualcosa o esce dallo schermo o finisce il contatore
        if(iter->b->get_counter() < 0 || iter->b->get_hit() || iter->b->get_position().x > lenS || iter->b->get_position().x < 1){
            iter->b->delete_item(0);
            remove_bullet(iter);
        }
        else{   // else muove il bullet con move
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