#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <ctime>

template<typename T>
class heap_node{
    public:
    T data;
    heap_node* left;
    heap_node* right;
    heap_node* parent;
    int Npl;
    heap_node<T>():left(NULL), right(NULL), parent(NULL), Npl(0){};
};

template <typename T>
class Heap{
    private:
    heap_node<T>* min;

    heap_node<T>* merge(heap_node<T>* h1, heap_node<T>* h2){
        if(h1 == NULL) return h2;
        if(h2 == NULL) return h1;
        heap_node<T>* max, *min, *p;
        if(h1->data > h2->data){
            min = h2;
            max = h1;
        }
        else{
            min = h1;
            max = h2;
        }
        // merge max to min
        if(min->left == NULL){
            min->left = max;
            min->left->parent = min;
        }
        else{
            min->right = merge(min->right, max);
            min->right->parent = min;
            if(min->right->Npl > min->left->Npl){
                p = min->left;
                min->left = min->right;
                min->right = p;
            }
            min->Npl = min->right->Npl + 1;
        }
        return min;
    }

    public:
    Heap(): min(NULL) { }
    ~Heap(){
        heap_node<T>* cur, *temp;
        cur = min;
        while(cur){
            if(cur->left != NULL){
                cur = cur->left;
            }
            else if(cur->right != NULL){
                cur = cur->right;
            }
            else{
                temp = cur->parent;
                if(temp){
                    if(temp->left == cur) temp->left = NULL;
                    if(temp->right == cur) temp->right = NULL;
                }
                //std::cout << "free node " << cur->data << std::endl;
                delete cur;
                cur = temp;
            }
        }
    }
    bool isEmpty(){
        if(min) return false;
        else return true;
    }
    T getMin(){
        if(!min) {
            throw "getMin failed";   
        }
        else return min->data;
    }
    heap_node<T>* insert(T data){
        heap_node<T>* p = new heap_node<T>();
        p->data = data;
        if(min == NULL){
            min = p;
            return p;
        }
        else{
            min = merge(min,p);
            return p;
        }
    }
    T deleteMin(){
        if(min == NULL) {
            throw "deleteMin failed";
        };
        
        T res = min->data;
        heap_node<T>* left, *right;
        left = min->left;
        right = min->right;
        //std::cout << "delete Min " << min->data << std::endl;
        delete min;
        if(left) left->parent = NULL;
        if(right) right->parent = NULL;
        min = merge(left, right);
        return res;
    }
    void decreaseKey(heap_node<T>* key, T sub){

        key->data = key->data - sub;
        if(key->parent == NULL) return ;

        heap_node<T>* p = key->parent;
        if(p->left == key) p->left = NULL;
        else if(p->right == key) p->right = NULL;
        key->parent = NULL;
        while(p->parent != NULL){ // root->parent = NULL
            if(p->left == NULL){
                // check child Npl and swap
                if(p->right != NULL){
                    p->left = p->right;
                    p->right = NULL;
                }
                else ;
                // refresh p Npl if necessary
                if(p->Npl == 0) break;
                else{
                    p->Npl = 0;
                    p = p->parent;
                }
            }
            else if(p->left != NULL){
                if(p->right == NULL){
                    // no need for swap
                    // refresh p Npl
                    if(p->Npl == 0) break;
                    else{
                        p->Npl = 0;
                        p = p->parent;
                    }
                }
                else if(p->right != NULL){
                    // swap
                    if(p->left->Npl < p->right->Npl){
                        heap_node<T>* t;
                        t = p->left;
                        p->left = p->right;
                        p->right = t;
                    }
                    // refresh
                    if(p->Npl == p->right->Npl+1) break;
                    else{
                        p->Npl = p->right->Npl + 1;
                        p = p->parent;
                    }
                }
            }
        }
        min = merge(min, key);
    }
};
