template <typename T>
struct node{
    node* next;
    node* prev;
    T val;
};

template <typename T>
struct cachedNode{
    node<T>* nodePointer;
    size_t idx;
};

template <typename T>
class list{
private:
    node<T>* head = new node<T>;
    node<T>* tail = new node<T>;
    cachedNode<T> cached;
    bool cachedSet = false;
    size_t listLen = 0;

    /*
        An optimised function to get a node's pointer given its idx in the list
    */
    node<T>* getNode(size_t idx){
        node<T>* fetchedNode;
        // Check if cached idx is closer to the target idx than the head or the tail
        if((
                (this->cached.idx > idx && this->cached.idx-idx < idx)  // cached idx is closer to the target idx than the head
            ||  (idx-this->cached.idx < this->listLen-idx) // cached idx is closer to the target idx than the tail
            ) 
            && this->cachedSet // cached node isnt invalid
        ){
            fetchedNode = this->cached.nodePointer; // Start from cached node
            if(this->cached.idx > idx){ // idx below middle, iter forwards
                int currIdx = this->cached.idx;
                while(currIdx > idx){
                    fetchedNode = fetchedNode->prev;
                    currIdx--;
                }
            }else{
                int currIdx = this->cached.idx;
                while(currIdx < idx){
                    fetchedNode = fetchedNode->next;
                    currIdx++;
                }
            }
        }else if(idx > this->listLen/2){ // idx above middle, iter backwards
            fetchedNode = this->tail;
            for(int i=0; i<listLen-idx-1; i++){
                fetchedNode = fetchedNode->prev;
            }
        }else{
            fetchedNode = this->head;
            for(int i=0; i<idx; i++){
                fetchedNode = fetchedNode->next;
            }
        }
        this->cached.nodePointer = fetchedNode;
        this->cached.idx = idx;
        cachedSet = true;
        return fetchedNode;
    }

public:
    ~list(){
        while(this->listLen){
            this->remove(0);
        }
    }

    void append(T v){
        node<T>* newTail = new node<T>;
        newTail->next = nullptr;
        newTail->prev = nullptr;
        newTail->val = v;
        if(this->listLen==0){
            this->head = newTail;
            this->tail = newTail;
        }else{
            newTail->prev = this->tail;
            this->tail->next = newTail;
            this->tail = newTail;
        }
        this->listLen++;
    }

    void insert(T v, size_t idx){
        if(idx > this->listLen){
            throw std::out_of_range("Index out of range");
        }
        // todo
    }

    T get(size_t idx){
        return this->getNode(idx)->val;
    }

    void remove(size_t idx){
        if(idx > this->listLen){
            throw std::out_of_range("Index out of range");
        }
        if(idx==0){ // Optimal way to remove first elem
            node<T>* tmp = this->head;
            this->head = this->head->next;
            delete tmp;
        }else if(idx==this->listLen-1){ // Optimal way to remove last elem
            node<T>* tmp = this->tail;
            this->tail = this->tail->prev;
            delete tmp;
        }else{
            node<T>* toRemove = this->getNode(idx);
            toRemove->prev->next = toRemove->next;
            toRemove->next->prev = toRemove->prev;
            this->cached.nodePointer = toRemove->next;
            delete toRemove;
        }
        this->listLen--;
    }

    size_t len(){
        return this->listLen;
    }

    void printDebugInfo(){
        // Iterate from head to tail, printing each node's value and its prev and next values
        node<T>* curr = this->head->next;
        for(int i=0; i<this->listLen-3; i++){
            std::cout << "Node: " << curr->val << " Prev: " << curr->prev->val << " Next: " << curr->next->val << "\n";
            curr = curr->next;
        }
    }

};
