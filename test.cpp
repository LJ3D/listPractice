#include <iostream>
#include "list.hpp"


int main(){

    LJLIST::list<int> lst;

    for(int i=0; i<10; i++){
        lst.append(rand()%10);
    }

    // Print list contents
    for(int i=0; i<lst.len(); i++){
        std::cout << lst.get(i) << ", ";
    }
    std::cout << std::endl;

    for(int i=0; i<3; i++){
        lst.insert(-1-i, 5);
    }

    // Print list contents
    for(int i=0; i<lst.len(); i++){
        std::cout << lst.get(i) << ", ";
    }
    std::cout << std::endl;

    return 0;
}