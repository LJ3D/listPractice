#include <iostream>
#include "list.hpp"


int main(){

    LJLIST::list<int> lst;

    for(int i=0; i<100; i++){
        lst.append(rand()%1000 - 500);
    }

    // Print list contents
    for(int i=0; i<lst.len(); i++){
        std::cout << lst.get(i) << ", ";
    }
    std::cout << std::endl;

    lst.sort();

    // Print list contents
    for(int i=0; i<lst.len(); i++){
        std::cout << lst.get(i) << ", ";
    }
    std::cout << std::endl;


    return 0;
}