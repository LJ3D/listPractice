template <typename T>
struct node{
    node* n;
    T v;
};

template <typename T>
class list{
private:
    node<T>* h = new node<T>;
    size_t l = 0;

public:

    void append(T v){
        node<T>* cn = this->h;
        for(int i=0; i<this->l; i++){
            cn = cn->n;
        }
        cn->v = v;
        cn->n = new node<T>;
        this->l++;
    }

    T get(size_t idx){
        if(idx > this->l){
            throw std::out_of_range("Index out of range");
        }
        node<T>* cn = this->h;
        for(int i=0; i<idx; i++){
            cn = cn->n;
        }
        return cn->v;
    }

    void remove(size_t idx){
        if(idx > this->l){
            throw std::out_of_range("Index out of range");
        }
        node<T>* cn = this->h;
        node<T>* bn = this->h;
        for(int i=0; i<idx; i++){
            cn = cn->n;
            if(i<idx-1){
                bn = cn;
            }
        }
        if(bn == cn){
            this->h = cn->n;
            delete cn;
        }else{
            bn->n = cn->n;
            delete cn;
        }
        this->l--;
    }

    size_t len(){
        return this->l;
    }

};
