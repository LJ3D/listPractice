#include <iostream>

#include "list.hpp"

int main(){
    list<int> lst;

    lst.append(69);
    lst.append(128);
    lst.append(23984);
    lst.append(-213);
    lst.append(69696969);

    while(lst.len()){
        std::cout << lst.get(0) << std::endl;
        lst.remove(0);
    }
    std::cout << "==========" << std::endl;

    for(int i=0; i<10; i++){
        lst.append(i);
    }

    for(int i=0; i<lst.len(); i++){
        std::cout << lst.get(i) << std::endl;
    }


    lst.get(1272398);

    return 0;
}