
template<typename T>
class heap_node{
    public:
    T data;
    bool mark;
    int degree;
    heap_node* left,*right;
    heap_node* parent,*firstchild;
    heap_node(){
        mark = true;
        degree = 0;
        left = right = this;
        parent = firstchild = nullptr;
    }
};
template<typename T>
using heapNode = heap_node<T>* ;

template<typename T>
class Heap{
    private:
    
    heap_node<T>* min;
    int times;
    int size; //you can refer to it when you have to create space
    //int size; //the maxsize of the trees
    void insert_left(heap_node<T>* base,heap_node<T>* operand){
        operand->left = base->left;
        operand->right = base;
        base->left->right = operand;
        base->left = operand;
    }
    void delete_relation(heap_node<T>* cur){
        cur->left->right = cur->right;
        cur->right->left = cur->left;
        cur->right = cur;
        cur->left = cur;  //point to itself!
        //delete cur;
    }
    //insert to the root array
    heap_node<T>* insert_to_root(heap_node<T>* cur){ 
        if(!cur->parent){
            cur->mark = true;
            return nullptr;
        }
        heap_node<T>* father = cur->parent;
        father->degree--;
        if(!father->degree){
            father->firstchild = nullptr;
        }else if(cur==father->firstchild){
            father->firstchild = cur->right;
        }
        //cur->parent = nullptr; //the parent is nullptr now
        delete_relation(cur);
        insert_left(min,cur);
        cur->parent = nullptr; //both the left and upwards directions!!!!!!
        cur->mark = true; //set to true
        if(cur->data<min->data){
            min = cur;
        }
        return father;
    }
    heap_node<T>* combine(heap_node<T>* first,heap_node<T>* second){
        heap_node<T>* min2,*max;
        if(first->data < second->data){ //according to the data comparison result
            min2 = first;
            max = second;
        }else{
            min2 = second;
            max = first;
            if(max==min){  //cope with the equalization situation
                min2 = first;
                max = second;
            }
        }
        // if(min2->data.node==987){
        //     first = second;
        //}
        delete_relation(max);
        heap_node<T>* firstchild = min2->firstchild;
        if(!firstchild){
            max->parent = min2;
            min2->firstchild = max;
        }else{
            max->parent = min2;
            insert_left(firstchild,max);
            min2->firstchild = max; //update the first child to let it points to the larger child
        }
        min2->degree++;
        return min2;
    }
    void recycle(heap_node<T>* cur){
        if(!cur){
            return;
        }
        heap_node<T>* next = cur->right;
        while(next!=cur){
            heap_node<T>* nnext = next->right;
            recycle(next->firstchild);
            delete next;
            next = nnext;
        }
        recycle(cur->firstchild);
        delete cur;
    }
    public:
    // just return node structrue of the input data for the usage of decreaseKey
    heap_node<T>* insert(const T& data){
        if(min == nullptr){ //update min if min is null
            min = new heap_node<T>() ;
            min->data = data;
            return min;
        }else{ 
            heap_node<T>* cur = new heap_node<T>();
            cur->data = data;
            insert_left(min,cur);  //just put it in the root array
            if(cur->data<min->data){
                min = cur;
            }
            return cur;
        }
    }
    T deleteMin(void){
        heap_node<T>* cur,*next;
        if(!min){
            throw("No element to be deleted");
        }
        T mindata = min->data;
        // if(min->firstchild){
        //     //if(min->firstchild->data.node == 1066||min->firstchild->data.node==3532||min->firstchild->data.node==3690){
        //     heap_node<T>* here = (heap_node<T>*)0x5872950;    
        //     for(int i=0;i<100;i++){
        //         here = (heap_node<T>*)((void*)here+0x10000);
        //         if(min == here){  
        //             times = times;
        //         } 
        //     }
            
        // }
        // if(min->data.node==987){
        //     times = times;
        // }
        if(min->right==min){//just one node at the root
            cur = min->firstchild;
            next = cur;
            for(int i=0;i<min->degree;i++){
                next->parent = nullptr;
                next = next->right;
            }
        }else{
            cur = min->right;
            next = min->firstchild;
            for(int i=0;i<min->degree;i++){
                heap_node<T>* nnext = next->right;
                delete_relation(next);
                insert_left(cur,next);
                next->parent = nullptr; //all the relations
                next = nnext;
            }
        }  //now cur is a node in the root array
        // times++;
        // if(times==982){
        //     times++ ;
        // }
        
        delete_relation(min);
        delete min;  //delete it now and return its data
        if(!cur){
            min = nullptr; //the tree is empty now
            return mindata;
        }
        next = cur->right;
        min = cur;
        int count = 0;
        int deg = min->degree;
        while(next!=cur){
            if(next->data < min->data){
                min = next;
            }
            if(next->degree > deg){
                deg = next->degree;   //find the number of trees we should maintain
            }
            next = next->right;
            count++;
        }
        count = deg+count; //the maximum anyway
        //now we find the minimum node at the root layer
        heap_node<T>** root_array = new heap_node<T>*[count+1];
        bool* taken = new bool[count+1]; //to record if the corresponding position has been taken up
        for(int i=0;i<count+1;i++){ //initialize to 0
            taken[i] = false;
            root_array[i] = nullptr;
        }
        cur = min; //point cur to min
        root_array[min->degree] = min;
        taken[min->degree] = 1;
        next = cur->right;
        while(next!=cur){
            int pos = next->degree;
            heap_node<T>* nnext = next->right;
            // if(next->data.node==1021){
            //     times = times&times;
            // }
            if(taken[pos]){ //has to merge
                while(taken[pos]){
                    // if(next==root_array[pos]){
                    //     times = times&times;
                    // }
                    next = combine(next,root_array[pos]); //combine the trees with same degrees
                    taken[pos] = false;
                    pos++;  
                }
                taken[pos] = true; //the degree add up with 1
                root_array[pos] = next;
            }else{
                taken[pos] = true;  //just take the position
                root_array[pos] = next;
            }
            next = nnext;
            // if(count>=5&&taken[5]==true){
            //     if(root_array[5]->data.node==1021){
            //       times = times&times;
            //     }
            // }
        }
        delete[] root_array;  //recycle in time
        delete[] taken;
        return mindata;
    }
    T getMin(void){
        return min->data;
    }
    bool isEmpty(){
        if(min){
            return false;
        }else{
            return true;
        }
    }
    //decreaseKey with heap_node<T> exploited
    void decreaseKey(heap_node<T>* cur, T decrement){
        cur->data -= decrement;
        if(!cur->parent){  //have no parent
            if(cur->data<min->data){
                min = cur;
            }
            return;
        }
        if(cur->data < cur->parent->data){
            //now we have to move cur
            heap_node<T>* father = insert_to_root(cur);
            //now we check the mark
            while(!father->mark){
                father = insert_to_root(father);
                if(!father){
                    return;
                }
                
            }
            if(father->parent){
                father->mark = false;
            }    
        }
        
    }
    Heap(int size = 100):size(size){
        min = nullptr; //initialize to nullptr for safety
        times = 0;
    }
    
    ~Heap(){  //avoid the usage of queue according to the representation method of fiboHeap
        recycle(min);
    }
};
