#include <iostream>
#include <cstdlib>
#include <ctime>


template<typename T>
class heap_node{
    public:
    T data;
    heap_node* firstchild,*parent,*nextsibling,*lastsibling;
    heap_node():firstchild(NULL),nextsibling(NULL),parent(NULL),lastsibling(NULL){};
};

template<typename T>
class Heap {
    private:
    heap_node<T>* min;
    
    void add_child(heap_node<T>* base, heap_node<T>* operand){
        // base and operand both are not null
        // operand->nextsibling == NULL (must)
        heap_node<T>* t;
        t = base->firstchild;
        base->firstchild = operand;
        operand->parent = base;
        if(t){
            operand->nextsibling = t;
            t->lastsibling = operand;
        }
    }
    heap_node<T>* merge(heap_node<T> *h1, heap_node<T> *h2){
        if(!h1) return h2;
        if(!h2) return h1;
        heap_node<T>* max,*min;
        if(h1->data < h2->data){
            min = h1;
            max = h2;
        }
        else {
            min = h2;
            max = h1;
        }
        add_child(min, max);
        
        return min;
    }
    
    public:
    Heap(): min(NULL) { };
    ~Heap(){
        if(min){
            heap_node<T>* temp, *cur;
            cur = min;
            while(cur){
                if(cur->firstchild) cur = cur->firstchild;
                else if(cur->nextsibling) cur = cur->nextsibling;
                else{
                    if(cur->lastsibling != NULL){
                        temp = cur->lastsibling;
                        temp->nextsibling = NULL;
                    }
                    else{
                        temp = cur->parent;
                        if(temp != NULL) temp->firstchild = NULL;
                    }
                    //std::cout << "free node" << cur->data << std::endl;
                    delete cur;
                    cur = temp;
                }
            }
        }
    };
    bool isEmpty(){
        if(!min) return true;
        else return false;
    }
    T getMin(){
        if(min == NULL) {                                                                                                                                                                                                                                                                                                                                   
            throw "getMin failed";
        }
        else return min->data;
    }
    heap_node<T>* insert(T data){
        if(!min){
            min = new heap_node<T>();
            min->data = data;
            return min;
        }
        else {
            heap_node<T>* cur = new heap_node<T>();
            cur->data = data;
            min = merge(min, cur);
            return cur;
        }
    }
    T deleteMin(){
        if(min == NULL) {
            throw "deleteMin failed";
        };

        T res = min->data;
        heap_node<T>* p = min->firstchild, *t, *last, *next;
        if(!p){
            //std::cout << "delete Min " << min->data << std::endl;
            delete min;
            min = NULL;
            return res;
        }
        else{
            for( ;p->nextsibling != NULL;p = p->nextsibling ){
                t = p->nextsibling;
                next = p->nextsibling->nextsibling;
                last = p->lastsibling;
                p->parent = t->parent = NULL;
                p->lastsibling = p->nextsibling = NULL;
                t->lastsibling = t->nextsibling = NULL;
                p = merge(p,t);
                p->nextsibling = next;
                if(next) next->lastsibling = p;
                p->lastsibling = last;
                if(last) last->nextsibling = p;

                if(p->nextsibling == NULL) break;
            }
            p->parent = NULL;
            for(;p->lastsibling != NULL;){
                t = p->lastsibling;
                last = p->lastsibling->lastsibling;
                next = p->nextsibling;
                p->lastsibling = p->nextsibling = NULL;
                t->lastsibling = t->nextsibling = NULL;
                p = merge(p,t);
                p->nextsibling = next;// NULL
                p->lastsibling = last;
                if(last) last->nextsibling = p;
            }
            //std::cout << "delete Min " << min->data << std::endl;
            delete min;
            min = p;
            return res;
        }
    }
    void decreaseKey(heap_node<T>* key, T sub){
        // find key and parent or lastsibling of key
        heap_node<T>* par,*sib;
        par = key->parent;
        sib = key->lastsibling; // the last sib of key
        //std::cout << "target: " << key->data << "parent: " << par->data << "lastsibling: " << sib->data ;
        key->data = key->data - sub;
        if(par == NULL) ;
        else if(sib == NULL){
            par->firstchild = key->nextsibling;
            if(key->nextsibling) key->nextsibling->lastsibling = NULL;
            key->nextsibling = NULL;
            key->parent = NULL;
            min = merge(min,key);
        }
        else if(sib != NULL){
            sib->nextsibling = key->nextsibling;
            if(key->nextsibling) key->nextsibling->lastsibling = sib;
            key->nextsibling = NULL;
            key->lastsibling = NULL;
            key->parent = NULL;
            min = merge(min,key);
        }
        return ;
    }
};
