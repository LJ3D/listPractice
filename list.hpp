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
    size_t listLen = 0;

    int dist(int x, int y){
        return (x-y)>0?x-y:x-y*-1;
    }

    /*
        An optimised function to get a node's pointer given its idx in the list
    */
    node<T>* getNode(size_t idx){
        node<T>* fetchedNode;
        // Check if cached idx is closer to the target idx than the head or the tail
        if(dist(this->cached.idx, idx) < idx || dist(this->cached.idx, idx) < this->listLen - idx){
            bool backwards = this->cached.idx > idx;
            int currIdx = this->cached.idx;
            fetchedNode = this->cached.nodePointer;
            while(currIdx != idx){
                fetchedNode = (backwards)? fetchedNode->prev : fetchedNode->next;
                currIdx += (backwards)? -1 : 1;
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
            std::cout << "remove debug info: " << toRemove->val << " " << toRemove->prev->val << " " << toRemove->next->val << "\n";
            toRemove->prev->next = toRemove->next;
            toRemove->next->prev = toRemove->prev;
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
