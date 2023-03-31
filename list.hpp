template <typename T>
struct node{
    node* n;
    node* l;
    T v;
};

template <typename T>
class list{
private:
    node<T>* h = new node<T>;
    node<T>* t = new node<T>;
    size_t l = 0;

public:
    ~list(){
        while(this->l>0){
            this->remove(0);
        }
    }

    void append(T v){
        node<T>* nt = new node<T>;
        nt->v = v;
        if(this->l==0){
            this->h = nt;
            this->t = nt;
        }else{
            nt->l = this->t;
            this->t->n = nt;
            this->t = nt;
        }
        this->l++;
    }

    void insert(T v, size_t idx){
        if(idx > this->l){
            throw std::out_of_range("Index out of range");
        }

        // todo
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

        if(idx==0){ // Optimal way to remove first elem
            node<T>* tmp = this->h;
            this->h = this->h->n;
            delete tmp;

        }else if(idx==this->l-1){ // Optimal way to remove last elem
            node<T>* tmp = this->t;
            this->t = this->t->l;
            delete tmp;

        }else if(idx > this->l/2){ // Go backwards if idx is greater than l/2, less iterations require
            node<T>* cn = this->t;
            node<T>* fn = this->t;
            for(int i=this->l-1; i>idx; i--){
                cn = cn->l;
                if(i>idx+1){
                    fn = cn;
                }
            }
            fn->l = cn->l;
            cn->l->n = fn;
            delete cn;

        }else{
            node<T>* cn = this->h;
            node<T>* bn = this->h;
            for(int i=0; i<idx; i++){
                cn = cn->n;
                if(i<idx-1){
                    bn = cn;
                }
            }
            bn->n = cn->n;
            cn->n->l = bn;
            delete cn;
        }

        this->l--;
    }

    size_t len(){
        return this->l;
    }

};
