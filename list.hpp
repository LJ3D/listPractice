#include <functional>

namespace LJLIST{

template <typename T>
struct node{
    node* next; // Next item in list
    node* prev; // Previous item in list
    T val;
};

/*
    For a cached node pointer to be useful, its place in the list must also be stored
    Also storing a boolean to indicate if the cache is set to a valid value or not
*/
template <typename T>
struct cachedNode{
    node<T>* nodePointer;
    size_t idx;
    bool set = false;
};

template <typename T>
class list{
private:
    node<T>* head = new node<T>; // First item in list
    node<T>* tail = new node<T>; // Last item in list
    size_t listLen = 0; // Number of items in list

    /*
        The cached node is used to improve the speed of sequential iterations through the list (but does also improve the speed of random selection from list),
        this is done by figuring out if the last node accessed by getNode() is closer to the current target node than either the head or tail node.
        
        This allows for speedy sequential access to the list without the end user of this class having to worry about using an iterator
    */
    cachedNode<T> cached;

    /*
        An optimised function to get a node's pointer given its idx in the list,
        optimised using the caching described above, as well as choosing the best starting point depending on if the target idx is above this->listLen/2
    */
    node<T>* getNode(size_t idx){
        node<T>* fetchedNode;
        // Check if cached idx is closer to the target idx than the head or the tail
        if(((this->cached.idx > idx && this->cached.idx-idx < idx)  // Cached idx is closer to the target idx than the head
                     || (idx-this->cached.idx < this->listLen-idx)) // Cached idx is closer to the target idx than the tail 
                                               && this->cached.set){ // And the cache is actually set
            fetchedNode = this->cached.nodePointer; // Start from cached node
            if(this->cached.idx > idx){ // Cached idx is greater than the target idx, so go backwards
               for(int i=this->cached.idx; i>idx; i--){
                   fetchedNode = fetchedNode->prev;
               }
            }else{ // Otherwise just go forwards
                for(int i=this->cached.idx; i<idx; i++){
                    fetchedNode = fetchedNode->next;
                }
            }
        }else if(idx > this->listLen/2){ // idx above middle, so start at the end of the list and go backwards
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
        // Update the cache:
        this->cached.nodePointer = fetchedNode;
        this->cached.idx = idx;
        this->cached.set = true;
        return fetchedNode;
    }

    /*
        Quicksort implementation
        Uses function pointer to allow for sorting in ascending or descending order
    */
    void qs(int startIdx, int endIdx, std::function<bool(T,T)> f) {
        if (endIdx - startIdx < 2) {
            return;
        }

        // Use last element as pivot
        int pivotIdx = endIdx - 1;
        T pivot = this->get(pivotIdx);

        // Compare first two elements with each other
        T first = this->get(startIdx);
        T second = this->get(startIdx + 1);
        if(!f(first, second)) {
            *(this->getPointer(startIdx)) = second;
            *(this->getPointer(startIdx + 1)) = first;
        }

        // 2 elements left = done
        if(endIdx - startIdx == 2){
            return;
        }

        // Iterate through the list comparing with the pivot
        // If the element is less than the pivot, swap it with the element at sortedIdx
        int sortedIdx = startIdx;
        for(int i=sortedIdx; i<endIdx; i++){
            if(f(this->get(i), pivot)){
                T tmp = this->get(i);
                *(this->getPointer(i)) = this->get(sortedIdx);
                *(this->getPointer(sortedIdx)) = tmp;
                sortedIdx++;
            }
        }

        // Swap the pivot with sortedIdx
        T tmp = this->get(sortedIdx);
        *(this->getPointer(sortedIdx)) = pivot;
        *(this->getPointer(pivotIdx)) = tmp;

        // Call recursively on the two new sublists
        this->qs(startIdx, sortedIdx, f);
        this->qs(sortedIdx + 1, endIdx, f);
    }

public:
    ~list(){
        while(this->listLen){
            this->remove(0);
        }
    }

    void append(T v){
        node<T>* newTail = new node<T>; // Allocates memory for a new node
        newTail->val = v; // Copy in the value
        if(this->listLen==0){ // If this is the first item in the list, then just set the head and tail to the new item
            this->head = newTail;
            this->tail = newTail;
        }else{
            newTail->prev = this->tail; // Set prev for the new node to be the previous tail
            this->tail->next = newTail; // Set the previous tails next node to the new node
            this->tail = newTail; // Set the tail to the new tail node
        }
        this->listLen++;
    }

    /*
        Works basically exactly the same as append,
        but replace the tail with the head
    */
    void prepend(T v){
        node<T>* newHead = new node<T>;
        newHead->val = v;
        if(this->listLen==0){
            this->head = newHead;
            this->tail = newHead;
        }else{
            newHead->next = this->head;
            this->head->prev = newHead;
            this->head = newHead;
        }
        this->listLen++;
        this->cached.idx++; // Dont forget to update the cached index!
    }

    /*
        Some extra names for appending and prepending that name them more like an std::list
    */
    void push_back(T v){
        this->append(v);
    }
    
    void push_front(T v){
        this->prepend(v);
    }

    void pop_back(){
        this->remove(this->listLen-1);
    }

    void pop_front(){
        this->remove(0);
    }

    void insert(T v, size_t idx){
        if(idx > this->listLen){
            throw std::out_of_range("Index out of range");
        }
        if(idx==0){ // Call the more minimal prepend() function instead of using getNode() if inserting at the beginning
            this->prepend(v);
        }else if(idx==this->listLen){ // or append() if at the end
            this->append(v);
        }else{
            node<T>* newNode = new node<T>; // Allocate a new node
            node<T>* nodeToInsertAt = this->getNode(idx); // Get a pointer to the node
            newNode->val = v; // Set the new node's value
            // Set the new node's pointers
            newNode->prev = nodeToInsertAt->prev;
            newNode->next = nodeToInsertAt;
            // Set the node before and after the new node's pointers to point to the new node
            nodeToInsertAt->prev->next = newNode;
            nodeToInsertAt->prev = newNode;
            this->listLen++;
            if(idx <= this->cached.idx){ // Update cache idx if necessary
                this->cached.idx++;
            }
        }
    }

    /*
        Gets a copy of the value at the given index
    */
    T get(size_t idx){
        return this->getNode(idx)->val;
    }

    /*
        Gets a pointer to the value at the given index
    */
    T* getPointer(size_t idx){
        return &(this->getNode(idx)->val);
    }

    void remove(size_t idx){
        if(idx > this->listLen){
            throw std::out_of_range("Index out of range");
        }
        if(idx==0){ // Optimal way to remove first elem (dont want to call getNode for no reason!)
            node<T>* tmp = this->head;
            this->head = this->head->next;
            delete tmp;
        }else if(idx==this->listLen-1){ // Optimal way to remove last elem
            node<T>* tmp = this->tail;
            this->tail = this->tail->prev;
            delete tmp;
        }else{
            node<T>* toRemove = this->getNode(idx);
            toRemove->prev->next = toRemove->next; // Set the previous nodes "next" to skip the toRemove node
            toRemove->next->prev = toRemove->prev; // And set the next nodes "prev" to also skip over the toRemove node
            if(this->cached.idx == idx){ // If the cached node is the one being removed, then set the cache to the next node
                this->cached.nodePointer = (toRemove == this->tail)? toRemove->prev : toRemove->next;
            }
            delete toRemove; // Now that no nodes are pointing to the toRemove node the memory can be freed
        }
        this->listLen--;
        if(idx < this->cached.idx){ // Update cache idx if the cached node has been "moved"
            this->cached.idx--;
        }
    }

    size_t len(){
        return this->listLen;
    }

    /*
        Sorts the entire list, optionally takes a function param to change the sorting order
        Function defaults to ascending order
    */
    void sort(std::function<bool(T,T)> f = [](T a, T b){return a<b;}) {
        this->qs(0, this->listLen, f);
    }
};

}