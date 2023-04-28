#include <iostream>
#include "list.hpp"


int main(){
    srand(time(NULL));
    LJLIST::list<int> lst;

    for(int i=0; i<50; i++){
        lst.append(rand()%100);
    }

    // Print list contents
    for(int i=0; i<lst.len(); i++){
        std::cout << lst.get(i) << ", ";
    }
    std::cout << std::endl;

    // Sort list
    lst.sort();

    // Print list contents
    for(int i=0; i<lst.len(); i++){
        std::cout << lst.get(i) << ", ";
    }
    std::cout << std::endl;


    return 0;
}